#include <stdio.h>
#include <stdlib.h>

#ifdef nti
# include <windows.h>
#endif
#include "mysql.h"

void printerror(MYSQL* m)
{
  printf("last err:%s\n",mysql_error(m));
}

int numOfCols(MYSQL_RES* r)
{
  if (r) 
    return mysql_num_fields(r);
  else
    return 0;
}

int numOfRows(MYSQL_RES* r)
{
  return mysql_num_rows(r);
}

void BMysql_getColumn(MYSQL_RES* r,int colno,char* columnname,char* ColumnNameType,int* datatype)
{
  MYSQL_FIELD* f;
  f = mysql_fetch_field_direct(r,colno-1);
  strcpy(columnname,f->name);
  switch (f->type) {
  case FIELD_TYPE_DECIMAL: 
    strcpy(ColumnNameType,"DECIMAL"); break;
  case FIELD_TYPE_TINY:  
    strcpy(ColumnNameType,"TINYINT");
    break;
  case FIELD_TYPE_SHORT:
    strcpy(ColumnNameType,"SMALLINT");
    break;
  case FIELD_TYPE_LONG: 
    strcpy(ColumnNameType,"INTEGER");
    break;
  case FIELD_TYPE_FLOAT:
    strcpy(ColumnNameType,"FLOAT");
    break;
  case FIELD_TYPE_DOUBLE:
    strcpy(ColumnNameType,"DOUBLE");
    break;
  case FIELD_TYPE_NULL:
    strcpy(ColumnNameType,"NULL");
    break;
  case FIELD_TYPE_TIMESTAMP:
    strcpy(ColumnNameType,"TIMESTAMP");
    break;
  case FIELD_TYPE_LONGLONG: 
    strcpy(ColumnNameType,"BIGINT");
    break;
  case FIELD_TYPE_INT24:
    strcpy(ColumnNameType,"MEDIUMINT");
    break;
  case FIELD_TYPE_DATE: 
    strcpy(ColumnNameType,"DATE");
    break;
  case FIELD_TYPE_TIME:
    strcpy(ColumnNameType,"TIME");
    break;
  case FIELD_TYPE_DATETIME: 
    strcpy(ColumnNameType,"DATETIME");
    break;
  case FIELD_TYPE_YEAR: 
    strcpy(ColumnNameType,"YEAR");
    break;
  case FIELD_TYPE_NEWDATE: 
    strcpy(ColumnNameType,"NEWDATE");
    break;
  case FIELD_TYPE_ENUM: 
    strcpy(ColumnNameType,"ENUM");
    break;
  case FIELD_TYPE_SET: 
    strcpy(ColumnNameType,"SET");
    break;
  case FIELD_TYPE_TINY_BLOB: 
    strcpy(ColumnNameType,"TINY_BLOB");
    break;
  case FIELD_TYPE_MEDIUM_BLOB: 
    strcpy(ColumnNameType,"MEDIUM_BLOB");
    break;
  case FIELD_TYPE_LONG_BLOB: 
    strcpy(ColumnNameType,"LONG_BLOB");
    break;
  case FIELD_TYPE_BLOB: 
    strcpy(ColumnNameType,"BLOB");
    break; 
  case FIELD_TYPE_VAR_STRING: 
    strcpy(ColumnNameType,"VARCHAR");
    break;
  case FIELD_TYPE_STRING: 
    strcpy(ColumnNameType,"STRING");
    break;
  };
  *datatype = f->type;

  /* fprintf(stderr,"Field %d is named %s, type=%d\n",colno,f->name,f->type);  */
}

int BMySql_getInteger(MYSQL_ROW r,int inx)
{
  return atoi(r[inx-1]);
}

char* BMySql_getText(MYSQL_ROW r,int inx)
{
  return r[inx-1];
}

double BMySql_getReal(MYSQL_ROW r,int inx)
{
  double t = atof(r[inx-1]);
  return t;
}

int BMySql_AffectedRows(MYSQL* con)
{
  return mysql_affected_rows(con);
}
