#include <stdio.h>
#include <stdlib.h>
#include "oci.h"

#define NEW(type) (type *)Malloc(sizeof(type))
#define MAXTEXTSIZE 256*1024
#define INITNOOFCOLS 1
#define INITNOOFROWS 1
#define TRUE 1
#define FALSE 0

typedef struct Result {
  int size;
  enum {intK, doubleK, stringK} kind;
  union {
    int intR;
    double doubleR; 
    char *stringR;
  } val;
} Result;

typedef struct ResultSet {
  Result ***rows;
  int numofrows;
  int numofcols;
} ResultSet;

// All arrays have their first element at position 1!!!
// (mimicking the way OCI does it)

void *Malloc(unsigned n)
{ void *p;

  if (!(p = malloc(n))) {
     fprintf(stderr,"Malloc(%d) failed.\n",n);
     fflush(stderr);
     abort();
   }
   return p;
}

ResultSet *OracleFetch(OCIStmt *stmthp, OCIError *errhp){
  int xs=0, ind=0, status=0, rowsdone=FALSE, colsdone=FALSE, trimdone=FALSE; 
  int currentcol=1, currentrow=1, currentNoOfCols=INITNOOFCOLS, currentNoOfRows=INITNOOFROWS, i=0;
  struct ResultSet *rs;
  unsigned int x;
  int *coltypes;
  void *paramhp;
  OCIDefine *defnhp;
  int errCode, MaxErrorSize=512;
  char *errBuf;

  rs = NEW(ResultSet);
  rs->numofrows=0;
  rs->numofcols=0;
  
  // Initialize the coltypes array (size +1 because all arrays here are 1-based)
  coltypes = (int *) Malloc((INITNOOFCOLS+1)*sizeof(int));
  for (i=0; i<=INITNOOFCOLS; i++){
    coltypes[i]=0;
  }

  // First find all the types of the columns and store them in coltypes...
  while (TRUE) {
    status = OCIParamGet(stmthp, OCI_HTYPE_STMT, errhp, &paramhp, currentcol);
    if (status!=OCI_SUCCESS) {
      break;
    }
    OCIAttrGet(paramhp, OCI_DTYPE_PARAM, &coltypes[currentcol], NULL, OCI_ATTR_DATA_TYPE, errhp);

    // convert type numeric (internal Oracle format) to type double:
    if (coltypes[currentcol]==2) coltypes[currentcol]=4; 
    
    currentcol++;
    rs->numofcols++;
    // If the coltypes array is full then expand it and initialize the tail
    if (currentcol>currentNoOfCols) {
      currentNoOfCols = currentNoOfCols*2;
      coltypes = (int *) realloc(coltypes, (currentNoOfCols+1)*sizeof(int));
      for (i=currentNoOfCols/2+1; i<=currentNoOfCols; i++) {
	coltypes[i]=0;
      }
    }
  }

  // Initialize the rows array (size +1 because all arrays here are 1-based)
  rs->rows = (Result ***) Malloc((INITNOOFROWS+1)*sizeof(Result**));
  for (i=0; i<=INITNOOFROWS; i++){
    rs->rows[i]=NULL;
  }

  // Now allocate space for the resultset and connect the pointers correctly
  while (!rowsdone) {
    // Expand rs->rows to accomodate more rows  
    if (currentrow>currentNoOfRows){
      currentNoOfRows = currentNoOfRows*2;
      rs->rows = (Result ***) realloc(rs->rows, (currentNoOfRows+1)*sizeof(Result **));
      for (i=currentNoOfRows/2+1; i<=currentNoOfRows; i++){
	rs->rows[i]=NULL;
      }
    }
    rs->rows[currentrow] = (Result**) Malloc((rs->numofcols+1)*sizeof(Result*));

    for (currentcol=1; currentcol <= rs->numofcols; currentcol++) {
      // Allocate the result in each cell of rs
      rs->rows[currentrow][currentcol] = NEW(Result);

      switch(coltypes[currentcol]){
      case SQLT_DAT: // time
      case SQLT_CHR: // text
      case SQLT_STR: // text
      case SQLT_VCS: // text
      case SQLT_LVC: // text
      case SQLT_AFC: // text
      case SQLT_AVC: // text
      case SQLT_VST: // text
	rs->rows[currentrow][currentcol]->kind = stringK;
	rs->rows[currentrow][currentcol]->size = MAXTEXTSIZE*sizeof(char);
	rs->rows[currentrow][currentcol]->val.stringR = (char *) Malloc(MAXTEXTSIZE*sizeof(char));
	for (i=0; i<MAXTEXTSIZE; i++){ rs->rows[currentrow][currentcol]->val.stringR[i]=' ';}
	status = OCIDefineByPos(stmthp, &defnhp, errhp, currentcol, rs->rows[currentrow][currentcol]->val.stringR, 
		     rs->rows[currentrow][currentcol]->size, coltypes[currentcol], &ind, NULL, NULL, OCI_DEFAULT);
	break;
      case SQLT_NUM: // int 
      case SQLT_INT: // int 
      case SQLT_VNU: // int 
      case SQLT_LNG: // int 
      case SQLT_RID: // int 
      case SQLT_UIN: // int 
      case SQLT_FLT: // real
	rs->rows[currentrow][currentcol]->kind = doubleK;
	rs->rows[currentrow][currentcol]->size = sizeof(double);
	rs->rows[currentrow][currentcol]->val.doubleR = 0; 
	status = OCIDefineByPos(stmthp, &defnhp, errhp, currentcol, &(rs->rows[currentrow][currentcol]->val.doubleR), 
		     rs->rows[currentrow][currentcol]->size, coltypes[currentcol], NULL, NULL, NULL, OCI_DEFAULT);
	break;
      case SQLT_ODT: // time
      case SQLT_DATE: // time
      case SQLT_TIME: // time
      case SQLT_TIMESTAMP: // time
	// HER BURDE VÆRE NOGET DATEHALLØJ!!!!!!!!
	break;
      };
    }
    // Now finally fetch data into allocated buffers
    status = OCIStmtFetch(stmthp, errhp, 1, OCI_FETCH_NEXT, OCI_DEFAULT);
    
    if (status != OCI_SUCCESS){
      errBuf = (char *) Malloc(MaxErrorSize*sizeof(char));
      OCIErrorGet(errhp, 1, 0, &errCode, errBuf, MaxErrorSize, OCI_HTYPE_ERROR);          
      printf("errcode: %d, error: %s, indicator: %i\n",errCode, errBuf, ind);
      status = OCIStmtFetch(stmthp, errhp, 1, OCI_FETCH_NEXT, OCI_DEFAULT);
      rowsdone=TRUE;
      rs->rows[currentrow]=NULL;
    }
    else {
      // Trim allocated textbuffers: remove all trailing blanks
      for (i=1; i<=rs->numofcols; i++){
	if (rs->rows[currentrow][i]->kind==stringK) {
	  xs=0;
	  trimdone=FALSE;
	  while (!trimdone){
	    if (rs->rows[currentrow][i]->val.stringR[MAXTEXTSIZE-xs-1]!=' ') trimdone=TRUE;      
	    else xs++;
	  }
	  rs->rows[currentrow][i]->val.stringR = 
	    (char *) realloc(rs->rows[currentrow][i]->val.stringR, MAXTEXTSIZE-xs+1);
	  rs->rows[currentrow][i]->val.stringR[MAXTEXTSIZE-xs] = 0;
	}
      }

      // Next row, please
      currentrow++;
    }
  }
  rs->numofrows = currentrow-1;
  return rs;
}


void OracleFreeResultSet(struct ResultSet *rs){
  int i, j;
  Result *currentRes;
  if (rs==NULL) return;
  for (i=1; i<=rs->numofrows; i++){
    for (j=1; j<=rs->numofcols; j++){
      currentRes = rs->rows[i][j];
      if (currentRes!=NULL){
	if (currentRes->kind==stringK) free(currentRes->val.stringR); 
	free(currentRes);
      }
    }
  }
  free(rs->rows);
  free(rs);
}


Result **OracleGetRowAtIndex(struct ResultSet *rs, int index){
  return rs->rows[index+1]; 
}


int OracleNumOfRows(struct ResultSet *rs){
  if (rs)
    return rs->numofrows;
  return 0;
}


int OracleNumOfCols(struct ResultSet *rs){
  if (rs)
    return rs->numofcols;
  return 0;
}


int OracleGetInteger(Result **row, int inx) {
  if (row && row[inx]){
    return ((int)row[inx]->val.doubleR);
  }
  return 0;
}

char* OracleGetText(Result **row, int inx) {
  int i=0;
  if (row && row[inx]) {
    return row[inx]->val.stringR;
  }
  return "";
}

double OracleGetReal(Result **row, int inx) {
  if (row && row[inx]){
    return (row[inx]->val.doubleR);
  }
  return 0.0;
}

int OracleGetColName(dvoid *paramhp, char *nameBufp, int maxsize, OCIError *errhp){
  char *buf=NULL;
  int status = OCIAttrGet(paramhp, OCI_DTYPE_PARAM, &buf, &maxsize, OCI_ATTR_NAME, errhp);
  int i=0;
  for (i=0; i<maxsize; i++)
    nameBufp[i]=buf[i];
  return status;
}
