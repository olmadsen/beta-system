ORIGIN '~beta/ast/current/astlevel'
-----------------------------------
 treelevellib:attributes
-----------------------------------

sql :  TreeLevel
(#
statement : cons(# #);

orderingColumn : cons(# #);

ASCorDESC : cons(# #);

columnAssignment : cons(# #);

insertItem : cons(# #);

predicate : cons(# #);

condition : predicate(# #);

compareCondition : condition(# #);

relationalExp : compareCondition(# #);

setOfScalars : cons(# #);

selectSpec : cons(# #);

selectItem : cons(# #);

newColumnId : cons(# #);

scalarExpr : cons(# #);

scalarTerm : scalarExpr(# #);

scalarValue : scalarTerm(# #);

aggregateReference : scalarValue(# #);

aggregateName : cons(# #);

functionReference : scalarValue(# #);

funcOne : cons(# #);

funcThree : cons(# #);

compareOperator : cons(# #);

constant : scalarValue(# #);

columnName : orderingColumn(# #);

dataType : cons(# #);

SQL : cons
(#
  getnameDecl: getson1(##);
  putnameDecl: putson1(##);
  getstatementList: getson2(##);
  putstatementList: putson2(##);
exit 1 #);

statementList : list(#exit 2 #);

selectStatement : statement
(#
  getselectExpression: getson1(##);
  putselectExpression: putson1(##);
  getorderingClauseOpt: getson2(##);
  putorderingClauseOpt: putson2(##);
exit 4 #);

orderingClause : cons
(#
  getorderItemList: getson1(##);
  putorderItemList: putson1(##);
exit 6 #);

orderItemList : list(#exit 7 #);

orderItem : cons
(#
  getorderingColumn: getson1(##);
  putorderingColumn: putson1(##);
  getASCorDESC: getson2(##);
  putASCorDESC: putson2(##);
exit 8 #);

ASC : ASCorDESC
(#
exit 11 #);

DESC : ASCorDESC
(#
exit 12 #);

updateStatement : statement
(#
  gettableName: getson1(##);
  puttableName: putson1(##);
  getaliasOpt: getson2(##);
  putaliasOpt: putson2(##);
  getcolumnAssignmentList: getson3(##);
  putcolumnAssignmentList: putson3(##);
  getwhereClauseOpt: getson4(##);
  putwhereClauseOpt: putson4(##);
exit 13 #);

columnAssignmentList : list(#exit 14 #);

nameAssignment : columnAssignment
(#
  getcolumnName: getson1(##);
  putcolumnName: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 16 #);

nullAssignment : columnAssignment
(#
exit 17 #);

deleteStatement : statement
(#
  gettableName: getson1(##);
  puttableName: putson1(##);
  getaliasOpt: getson2(##);
  putaliasOpt: putson2(##);
  getwhereClauseOpt: getson3(##);
  putwhereClauseOpt: putson3(##);
exit 18 #);

insertStatement : statement
(#
  gettableName: getson1(##);
  puttableName: putson1(##);
  getcolumnSpecificationOpt: getson2(##);
  putcolumnSpecificationOpt: putson2(##);
  getinsertItemList: getson3(##);
  putinsertItemList: putson3(##);
exit 20 #);

columnSpecification : cons
(#
  getcolumnNameList: getson1(##);
  putcolumnNameList: putson1(##);
exit 22 #);

columnNameList : list(#exit 23 #);

insertItemList : list(#exit 24 #);

constantItem : insertItem
(#
  getconstant: getson1(##);
  putconstant: putson1(##);
exit 26 #);

nullItem : insertItem
(#
exit 27 #);

andCondition : predicate
(#
  getcondition: getson1(##);
  putcondition: putson1(##);
  getcondition: getson2(##);
  putcondition: putson2(##);
exit 30 #);

orCondition : predicate
(#
  getcondition: getson1(##);
  putcondition: putson1(##);
  getcondition: getson2(##);
  putcondition: putson2(##);
exit 31 #);

notCondition : predicate
(#
  getcondition: getson1(##);
  putcondition: putson1(##);
exit 32 #);

compareEQ : relationalExp
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 35 #);

compareNE : relationalExp
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 36 #);

compareLT : relationalExp
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 37 #);

compareLE : relationalExp
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 38 #);

compareGT : relationalExp
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 39 #);

compareGE : relationalExp
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 40 #);

nullCompare : compareCondition
(#
exit 41 #);

notNullCompare : compareCondition
(#
exit 42 #);

betweenCondition : condition
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getnotOpt: getson2(##);
  putnotOpt: putson2(##);
  getscalarExpr: getson3(##);
  putscalarExpr: putson3(##);
  getscalarExpr: getson4(##);
  putscalarExpr: putson4(##);
exit 43 #);

not : cons
(#
exit 45 #);

likeCondition : condition
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getnotOpt: getson2(##);
  putnotOpt: putson2(##);
  getscalarExpr: getson3(##);
  putscalarExpr: putson3(##);
exit 46 #);

inCondition : condition
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
  getnotOpt: getson2(##);
  putnotOpt: putson2(##);
  getsetOfScalarsList: getson3(##);
  putsetOfScalarsList: putson3(##);
exit 47 #);

setOfScalarsList : list(#exit 48 #);

singletonSet : setOfScalars
(#
  getconstant: getson1(##);
  putconstant: putson1(##);
exit 50 #);

setRange : setOfScalars
(#
  getconstant: getson1(##);
  putconstant: putson1(##);
  getconstant: getson2(##);
  putconstant: putson2(##);
exit 51 #);

bracketedPredicate : condition
(#
  getpredicate: getson1(##);
  putpredicate: putson1(##);
exit 52 #);

selectExpression : cons
(#
  getselectClause: getson1(##);
  putselectClause: putson1(##);
  getfromClause: getson2(##);
  putfromClause: putson2(##);
  getwhereClauseOpt: getson3(##);
  putwhereClauseOpt: putson3(##);
  getgroupingHavingClauseOpt: getson4(##);
  putgroupingHavingClauseOpt: putson4(##);
exit 53 #);

selectClause : cons
(#
  getdistinctOpt: getson1(##);
  putdistinctOpt: putson1(##);
  getselectSpec: getson2(##);
  putselectSpec: putson2(##);
exit 54 #);

distinct : cons
(#
exit 56 #);

all : selectSpec
(#
exit 58 #);

selectItems : selectSpec
(#
  getselectItemList: getson1(##);
  putselectItemList: putson1(##);
exit 59 #);

selectItemList : list(#exit 60 #);

selectItemA : selectItem
(#
  gettableName: getson1(##);
  puttableName: putson1(##);
exit 62 #);

selectItemB : selectItem
(#
  getAmpScalarExprList: getson1(##);
  putAmpScalarExprList: putson1(##);
  getspecialNDsyntaxOpt: getson2(##);
  putspecialNDsyntaxOpt: putson2(##);
exit 63 #);

AmpScalarExprList : list(#exit 64 #);

AmpScalarExpr : cons
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
exit 65 #);

specialNDsyntax : cons
(#
  getconvertOpt: getson1(##);
  putconvertOpt: putson1(##);
  getdisplayOpt: getson2(##);
  putdisplayOpt: putson2(##);
  getnewColumnId: getson3(##);
  putnewColumnId: putson3(##);
exit 67 #);

convert : cons
(#
  getdataType: getson1(##);
  putdataType: putson1(##);
exit 69 #);

display : cons
(#
  getdisplayString: getson1(##);
  putdisplayString: putson1(##);
exit 71 #);

fromClause : cons
(#
  getfromItemList: getson1(##);
  putfromItemList: putson1(##);
exit 73 #);

fromItemList : list(#exit 74 #);

fromItem : cons
(#
  gettableName: getson1(##);
  puttableName: putson1(##);
  getaliasOpt: getson2(##);
  putaliasOpt: putson2(##);
exit 75 #);

whereClause : cons
(#
  getpredicate: getson1(##);
  putpredicate: putson1(##);
exit 77 #);

groupingClause : cons
(#
  getcolumnNameList: getson1(##);
  putcolumnNameList: putson1(##);
exit 78 #);

havingClause : cons
(#
  getcompareOperator: getson1(##);
  putcompareOperator: putson1(##);
  getconstant: getson2(##);
  putconstant: putson2(##);
exit 80 #);

groupingHavingClause : cons
(#
  getgroupingClause: getson1(##);
  putgroupingClause: putson1(##);
  gethavingClauseOpt: getson2(##);
  puthavingClauseOpt: putson2(##);
exit 82 #);

plusExpr : scalarExpr
(#
  getscalarTerm: getson1(##);
  putscalarTerm: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 84 #);

minusExpr : scalarExpr
(#
  getscalarTerm: getson1(##);
  putscalarTerm: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 85 #);

multExpr : scalarExpr
(#
  getscalarTerm: getson1(##);
  putscalarTerm: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 86 #);

divExpr : scalarExpr
(#
  getscalarTerm: getson1(##);
  putscalarTerm: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 87 #);

countReferenceA : aggregateReference
(#
exit 91 #);

countReferenceB : aggregateReference
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
exit 92 #);

aggregateA : aggregateReference
(#
  getaggregatename: getson1(##);
  putaggregatename: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 93 #);

aggregateB : aggregateReference
(#
  getaggregateName: getson1(##);
  putaggregateName: putson1(##);
  getcolumnName: getson2(##);
  putcolumnName: putson2(##);
exit 94 #);

sum : aggregateName
(#
exit 96 #);

avg : aggregateName
(#
exit 97 #);

max : aggregateName
(#
exit 98 #);

min : aggregateName
(#
exit 99 #);

stdev : aggregateName
(#
exit 100 #);

variance : aggregateName
(#
exit 101 #);

funcOneRef : functionReference
(#
  getfuncOne: getson1(##);
  putfuncOne: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
exit 103 #);

funcThreeRef : functionReference
(#
  getfuncThree: getson1(##);
  putfuncThree: putson1(##);
  getscalarExpr: getson2(##);
  putscalarExpr: putson2(##);
  getconst: getson3(##);
  putconst: putson3(##);
  getconst: getson4(##);
  putconst: putson4(##);
exit 104 #);

mod : funcOne
(#
exit 106 #);

sqrt : funcOne
(#
exit 107 #);

toChar : funcOne
(#
exit 108 #);

toNumber : funcOne
(#
exit 109 #);

length : funcOne
(#
exit 110 #);

round : funcOne
(#
exit 111 #);

trunc : funcOne
(#
exit 112 #);

abs : funcOne
(#
exit 113 #);

upper : funcOne
(#
exit 114 #);

lower : funcOne
(#
exit 115 #);

initCap : funcOne
(#
exit 116 #);

substr : funcThree
(#
exit 118 #);

bits : funcThree
(#
exit 119 #);

bracketedExpr : scalarValue
(#
  getscalarExpr: getson1(##);
  putscalarExpr: putson1(##);
exit 120 #);

scalarName : scalarValue
(#
  getcolumnName: getson1(##);
  putcolumnName: putson1(##);
exit 121 #);

eq : compareOperator
(#
exit 123 #);

ne : compareOperator
(#
exit 124 #);

lt : compareOperator
(#
exit 125 #);

le : compareOperator
(#
exit 126 #);

gt : compareOperator
(#
exit 127 #);

ge : compareOperator
(#
exit 128 #);

integerConstant : constant
(#
  getconst: getson1(##);
  putconst: putson1(##);
exit 130 #);

realConstant : constant
(#
  getconst: getson1(##);
  putconst: putson1(##);
  getconst: getson2(##);
  putconst: putson2(##);
exit 131 #);

stringConstant : constant
(#
  getstring: getson1(##);
  putstring: putson1(##);
exit 132 #);

inputParameter : scalarValue
(#
  getnameAppl: getson1(##);
  putnameAppl: putson1(##);
exit 133 #);

tablename : cons
(#
  getnameAppl: getson1(##);
  putnameAppl: putson1(##);
exit 134 #);

alias : cons
(#
  getnameAppl: getson1(##);
  putnameAppl: putson1(##);
exit 135 #);

explicitTableName : columnName
(#
  gettableName: getson1(##);
  puttableName: putson1(##);
  getnameAppl: getson2(##);
  putnameAppl: putson2(##);
exit 137 #);

implicitTableName : columnName
(#
  getnameAppl: getson1(##);
  putnameAppl: putson1(##);
exit 138 #);

integerDouble : dataType
(#
exit 140 #);

integerQuad : dataType
(#
exit 141 #);

realQuad : dataType
(#
exit 142 #);

realDoubleQuad : dataType
(#
exit 143 #);

character : dataType
(#
  getconst: getson1(##);
  putconst: putson1(##);
exit 144 #);

numeric : dataType
(#
  getconst: getson1(##);
  putconst: putson1(##);
exit 145 #);

bcd : dataType
(#
  getconst: getson1(##);
  putconst: putson1(##);
  getconst: getson2(##);
  putconst: putson2(##);
exit 146 #);

displayString : cons
(#
  getstring: getson1(##);
  putstring: putson1(##);
exit 147 #);

columnInteger : orderingColumn
(#
  getconst: getson1(##);
  putconst: putson1(##);
exit 148 #);

columnIdName : newColumnId
(#
  getnameAppl: getson1(##);
  putnameAppl: putson1(##);
exit 149 #);

columnIdString : newColumnId
(#
  getstring: getson1(##);
  putstring: putson1(##);
exit 150 #);

  grammarIdentification ::< (# do 'sql' -> theGrammarName #);

  version ::< (# do 1 -> versNo #);

  suffix ::< (# do '.sql' -> theSuffix #);

  maxproductions ::< (# do 150 -> maxProd #); 

  init ::<

(#
do
  &(# do 
    1 -> kindArray[1]; 0 -> roomArray[1]; 2 -> sonArray[1]; 
    &referenceGenerator(# do &SQL[] -> as[] #)[] -> genRefArray[1][];
    1 -> kindArray[2]; 0 -> roomArray[2]; 0 -> sonArray[2]; 
    &referenceGenerator(# do &statementList[] -> as[] #)[] -> genRefArray[2][];
    2 -> kindArray[3]; 2 -> roomArray[3]; 0 -> sonArray[3]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[3][];
    1 -> kindArray[4]; 0 -> roomArray[4]; 2 -> sonArray[4]; 
    &referenceGenerator(# do &selectStatement[] -> as[] #)[] -> genRefArray[4][];
    3 -> kindArray[5]; 2 -> roomArray[5]; 0 -> sonArray[5]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[5][];
    1 -> kindArray[6]; 0 -> roomArray[6]; 1 -> sonArray[6]; 
    &referenceGenerator(# do &orderingClause[] -> as[] #)[] -> genRefArray[6][];
    1 -> kindArray[7]; 0 -> roomArray[7]; 0 -> sonArray[7]; 
    &referenceGenerator(# do &orderItemList[] -> as[] #)[] -> genRefArray[7][];
    1 -> kindArray[8]; 0 -> roomArray[8]; 2 -> sonArray[8]; 
    &referenceGenerator(# do &orderItem[] -> as[] #)[] -> genRefArray[8][];
    2 -> kindArray[9]; 2 -> roomArray[9]; 0 -> sonArray[9]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[9][];
    2 -> kindArray[10]; 2 -> roomArray[10]; 0 -> sonArray[10]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[10][];
    1 -> kindArray[11]; 0 -> roomArray[11]; 0 -> sonArray[11]; 
    &referenceGenerator(# do &ASC[] -> as[] #)[] -> genRefArray[11][];
    1 -> kindArray[12]; 0 -> roomArray[12]; 0 -> sonArray[12]; 
    &referenceGenerator(# do &DESC[] -> as[] #)[] -> genRefArray[12][];
    1 -> kindArray[13]; 0 -> roomArray[13]; 4 -> sonArray[13]; 
    &referenceGenerator(# do &updateStatement[] -> as[] #)[] -> genRefArray[13][];
    1 -> kindArray[14]; 0 -> roomArray[14]; 0 -> sonArray[14]; 
    &referenceGenerator(# do &columnAssignmentList[] -> as[] #)[] -> genRefArray[14][];
    2 -> kindArray[15]; 2 -> roomArray[15]; 0 -> sonArray[15]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[15][];
    1 -> kindArray[16]; 0 -> roomArray[16]; 2 -> sonArray[16]; 
    &referenceGenerator(# do &nameAssignment[] -> as[] #)[] -> genRefArray[16][];
    1 -> kindArray[17]; 0 -> roomArray[17]; 0 -> sonArray[17]; 
    &referenceGenerator(# do &nullAssignment[] -> as[] #)[] -> genRefArray[17][];
    1 -> kindArray[18]; 0 -> roomArray[18]; 3 -> sonArray[18]; 
    &referenceGenerator(# do &deleteStatement[] -> as[] #)[] -> genRefArray[18][];
    3 -> kindArray[19]; 2 -> roomArray[19]; 0 -> sonArray[19]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[19][];
  #);
  &(# do
    1 -> kindArray[20]; 0 -> roomArray[20]; 3 -> sonArray[20]; 
    &referenceGenerator(# do &insertStatement[] -> as[] #)[] -> genRefArray[20][];
    3 -> kindArray[21]; 2 -> roomArray[21]; 0 -> sonArray[21]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[21][];
    1 -> kindArray[22]; 0 -> roomArray[22]; 1 -> sonArray[22]; 
    &referenceGenerator(# do &columnSpecification[] -> as[] #)[] -> genRefArray[22][];
    1 -> kindArray[23]; 0 -> roomArray[23]; 0 -> sonArray[23]; 
    &referenceGenerator(# do &columnNameList[] -> as[] #)[] -> genRefArray[23][];
    1 -> kindArray[24]; 0 -> roomArray[24]; 0 -> sonArray[24]; 
    &referenceGenerator(# do &insertItemList[] -> as[] #)[] -> genRefArray[24][];
    2 -> kindArray[25]; 2 -> roomArray[25]; 0 -> sonArray[25]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[25][];
    1 -> kindArray[26]; 0 -> roomArray[26]; 1 -> sonArray[26]; 
    &referenceGenerator(# do &constantItem[] -> as[] #)[] -> genRefArray[26][];
    1 -> kindArray[27]; 0 -> roomArray[27]; 0 -> sonArray[27]; 
    &referenceGenerator(# do &nullItem[] -> as[] #)[] -> genRefArray[27][];
    2 -> kindArray[28]; 2 -> roomArray[28]; 0 -> sonArray[28]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[28][];
    2 -> kindArray[29]; 2 -> roomArray[29]; 0 -> sonArray[29]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[29][];
    1 -> kindArray[30]; 0 -> roomArray[30]; 2 -> sonArray[30]; 
    &referenceGenerator(# do &andCondition[] -> as[] #)[] -> genRefArray[30][];
    1 -> kindArray[31]; 0 -> roomArray[31]; 2 -> sonArray[31]; 
    &referenceGenerator(# do &orCondition[] -> as[] #)[] -> genRefArray[31][];
    1 -> kindArray[32]; 0 -> roomArray[32]; 1 -> sonArray[32]; 
    &referenceGenerator(# do &notCondition[] -> as[] #)[] -> genRefArray[32][];
    2 -> kindArray[33]; 2 -> roomArray[33]; 0 -> sonArray[33]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[33][];
    2 -> kindArray[34]; 2 -> roomArray[34]; 0 -> sonArray[34]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[34][];
    1 -> kindArray[35]; 0 -> roomArray[35]; 2 -> sonArray[35]; 
    &referenceGenerator(# do &compareEQ[] -> as[] #)[] -> genRefArray[35][];
    1 -> kindArray[36]; 0 -> roomArray[36]; 2 -> sonArray[36]; 
    &referenceGenerator(# do &compareNE[] -> as[] #)[] -> genRefArray[36][];
    1 -> kindArray[37]; 0 -> roomArray[37]; 2 -> sonArray[37]; 
    &referenceGenerator(# do &compareLT[] -> as[] #)[] -> genRefArray[37][];
    1 -> kindArray[38]; 0 -> roomArray[38]; 2 -> sonArray[38]; 
    &referenceGenerator(# do &compareLE[] -> as[] #)[] -> genRefArray[38][];
    1 -> kindArray[39]; 0 -> roomArray[39]; 2 -> sonArray[39]; 
    &referenceGenerator(# do &compareGT[] -> as[] #)[] -> genRefArray[39][];
  #);
  &(# do
    1 -> kindArray[40]; 0 -> roomArray[40]; 2 -> sonArray[40]; 
    &referenceGenerator(# do &compareGE[] -> as[] #)[] -> genRefArray[40][];
    1 -> kindArray[41]; 0 -> roomArray[41]; 0 -> sonArray[41]; 
    &referenceGenerator(# do &nullCompare[] -> as[] #)[] -> genRefArray[41][];
    1 -> kindArray[42]; 0 -> roomArray[42]; 0 -> sonArray[42]; 
    &referenceGenerator(# do &notNullCompare[] -> as[] #)[] -> genRefArray[42][];
    1 -> kindArray[43]; 0 -> roomArray[43]; 4 -> sonArray[43]; 
    &referenceGenerator(# do &betweenCondition[] -> as[] #)[] -> genRefArray[43][];
    3 -> kindArray[44]; 2 -> roomArray[44]; 0 -> sonArray[44]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[44][];
    1 -> kindArray[45]; 0 -> roomArray[45]; 0 -> sonArray[45]; 
    &referenceGenerator(# do &not[] -> as[] #)[] -> genRefArray[45][];
    1 -> kindArray[46]; 0 -> roomArray[46]; 3 -> sonArray[46]; 
    &referenceGenerator(# do &likeCondition[] -> as[] #)[] -> genRefArray[46][];
    1 -> kindArray[47]; 0 -> roomArray[47]; 3 -> sonArray[47]; 
    &referenceGenerator(# do &inCondition[] -> as[] #)[] -> genRefArray[47][];
    1 -> kindArray[48]; 0 -> roomArray[48]; 0 -> sonArray[48]; 
    &referenceGenerator(# do &setOfScalarsList[] -> as[] #)[] -> genRefArray[48][];
    2 -> kindArray[49]; 2 -> roomArray[49]; 0 -> sonArray[49]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[49][];
    1 -> kindArray[50]; 0 -> roomArray[50]; 1 -> sonArray[50]; 
    &referenceGenerator(# do &singletonSet[] -> as[] #)[] -> genRefArray[50][];
    1 -> kindArray[51]; 0 -> roomArray[51]; 2 -> sonArray[51]; 
    &referenceGenerator(# do &setRange[] -> as[] #)[] -> genRefArray[51][];
    1 -> kindArray[52]; 0 -> roomArray[52]; 1 -> sonArray[52]; 
    &referenceGenerator(# do &bracketedPredicate[] -> as[] #)[] -> genRefArray[52][];
    1 -> kindArray[53]; 0 -> roomArray[53]; 4 -> sonArray[53]; 
    &referenceGenerator(# do &selectExpression[] -> as[] #)[] -> genRefArray[53][];
    1 -> kindArray[54]; 0 -> roomArray[54]; 2 -> sonArray[54]; 
    &referenceGenerator(# do &selectClause[] -> as[] #)[] -> genRefArray[54][];
    3 -> kindArray[55]; 2 -> roomArray[55]; 0 -> sonArray[55]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[55][];
    1 -> kindArray[56]; 0 -> roomArray[56]; 0 -> sonArray[56]; 
    &referenceGenerator(# do &distinct[] -> as[] #)[] -> genRefArray[56][];
    2 -> kindArray[57]; 2 -> roomArray[57]; 0 -> sonArray[57]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[57][];
    1 -> kindArray[58]; 0 -> roomArray[58]; 0 -> sonArray[58]; 
    &referenceGenerator(# do &all[] -> as[] #)[] -> genRefArray[58][];
    1 -> kindArray[59]; 0 -> roomArray[59]; 1 -> sonArray[59]; 
    &referenceGenerator(# do &selectItems[] -> as[] #)[] -> genRefArray[59][];
  #);
  &(# do
    1 -> kindArray[60]; 0 -> roomArray[60]; 0 -> sonArray[60]; 
    &referenceGenerator(# do &selectItemList[] -> as[] #)[] -> genRefArray[60][];
    2 -> kindArray[61]; 2 -> roomArray[61]; 0 -> sonArray[61]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[61][];
    1 -> kindArray[62]; 0 -> roomArray[62]; 1 -> sonArray[62]; 
    &referenceGenerator(# do &selectItemA[] -> as[] #)[] -> genRefArray[62][];
    1 -> kindArray[63]; 0 -> roomArray[63]; 2 -> sonArray[63]; 
    &referenceGenerator(# do &selectItemB[] -> as[] #)[] -> genRefArray[63][];
    1 -> kindArray[64]; 0 -> roomArray[64]; 0 -> sonArray[64]; 
    &referenceGenerator(# do &AmpScalarExprList[] -> as[] #)[] -> genRefArray[64][];
    1 -> kindArray[65]; 0 -> roomArray[65]; 1 -> sonArray[65]; 
    &referenceGenerator(# do &AmpScalarExpr[] -> as[] #)[] -> genRefArray[65][];
    3 -> kindArray[66]; 2 -> roomArray[66]; 0 -> sonArray[66]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[66][];
    1 -> kindArray[67]; 0 -> roomArray[67]; 3 -> sonArray[67]; 
    &referenceGenerator(# do &specialNDsyntax[] -> as[] #)[] -> genRefArray[67][];
    3 -> kindArray[68]; 2 -> roomArray[68]; 0 -> sonArray[68]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[68][];
    1 -> kindArray[69]; 0 -> roomArray[69]; 1 -> sonArray[69]; 
    &referenceGenerator(# do &convert[] -> as[] #)[] -> genRefArray[69][];
    3 -> kindArray[70]; 2 -> roomArray[70]; 0 -> sonArray[70]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[70][];
    1 -> kindArray[71]; 0 -> roomArray[71]; 1 -> sonArray[71]; 
    &referenceGenerator(# do &display[] -> as[] #)[] -> genRefArray[71][];
    2 -> kindArray[72]; 2 -> roomArray[72]; 0 -> sonArray[72]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[72][];
    1 -> kindArray[73]; 0 -> roomArray[73]; 1 -> sonArray[73]; 
    &referenceGenerator(# do &fromClause[] -> as[] #)[] -> genRefArray[73][];
    1 -> kindArray[74]; 0 -> roomArray[74]; 0 -> sonArray[74]; 
    &referenceGenerator(# do &fromItemList[] -> as[] #)[] -> genRefArray[74][];
    1 -> kindArray[75]; 0 -> roomArray[75]; 2 -> sonArray[75]; 
    &referenceGenerator(# do &fromItem[] -> as[] #)[] -> genRefArray[75][];
    3 -> kindArray[76]; 2 -> roomArray[76]; 0 -> sonArray[76]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[76][];
    1 -> kindArray[77]; 0 -> roomArray[77]; 1 -> sonArray[77]; 
    &referenceGenerator(# do &whereClause[] -> as[] #)[] -> genRefArray[77][];
    1 -> kindArray[78]; 0 -> roomArray[78]; 1 -> sonArray[78]; 
    &referenceGenerator(# do &groupingClause[] -> as[] #)[] -> genRefArray[78][];
    3 -> kindArray[79]; 2 -> roomArray[79]; 0 -> sonArray[79]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[79][];
  #);
  &(# do
    1 -> kindArray[80]; 0 -> roomArray[80]; 2 -> sonArray[80]; 
    &referenceGenerator(# do &havingClause[] -> as[] #)[] -> genRefArray[80][];
    3 -> kindArray[81]; 2 -> roomArray[81]; 0 -> sonArray[81]; 
    &referenceGenerator(# do &Optional[] -> as[] #)[] -> genRefArray[81][];
    1 -> kindArray[82]; 0 -> roomArray[82]; 2 -> sonArray[82]; 
    &referenceGenerator(# do &groupingHavingClause[] -> as[] #)[] -> genRefArray[82][];
    2 -> kindArray[83]; 2 -> roomArray[83]; 0 -> sonArray[83]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[83][];
    1 -> kindArray[84]; 0 -> roomArray[84]; 2 -> sonArray[84]; 
    &referenceGenerator(# do &plusExpr[] -> as[] #)[] -> genRefArray[84][];
    1 -> kindArray[85]; 0 -> roomArray[85]; 2 -> sonArray[85]; 
    &referenceGenerator(# do &minusExpr[] -> as[] #)[] -> genRefArray[85][];
    1 -> kindArray[86]; 0 -> roomArray[86]; 2 -> sonArray[86]; 
    &referenceGenerator(# do &multExpr[] -> as[] #)[] -> genRefArray[86][];
    1 -> kindArray[87]; 0 -> roomArray[87]; 2 -> sonArray[87]; 
    &referenceGenerator(# do &divExpr[] -> as[] #)[] -> genRefArray[87][];
    2 -> kindArray[88]; 2 -> roomArray[88]; 0 -> sonArray[88]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[88][];
    2 -> kindArray[89]; 2 -> roomArray[89]; 0 -> sonArray[89]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[89][];
    2 -> kindArray[90]; 2 -> roomArray[90]; 0 -> sonArray[90]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[90][];
    1 -> kindArray[91]; 0 -> roomArray[91]; 0 -> sonArray[91]; 
    &referenceGenerator(# do &countReferenceA[] -> as[] #)[] -> genRefArray[91][];
    1 -> kindArray[92]; 0 -> roomArray[92]; 1 -> sonArray[92]; 
    &referenceGenerator(# do &countReferenceB[] -> as[] #)[] -> genRefArray[92][];
    1 -> kindArray[93]; 0 -> roomArray[93]; 2 -> sonArray[93]; 
    &referenceGenerator(# do &aggregateA[] -> as[] #)[] -> genRefArray[93][];
    1 -> kindArray[94]; 0 -> roomArray[94]; 2 -> sonArray[94]; 
    &referenceGenerator(# do &aggregateB[] -> as[] #)[] -> genRefArray[94][];
    2 -> kindArray[95]; 2 -> roomArray[95]; 0 -> sonArray[95]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[95][];
    1 -> kindArray[96]; 0 -> roomArray[96]; 0 -> sonArray[96]; 
    &referenceGenerator(# do &sum[] -> as[] #)[] -> genRefArray[96][];
    1 -> kindArray[97]; 0 -> roomArray[97]; 0 -> sonArray[97]; 
    &referenceGenerator(# do &avg[] -> as[] #)[] -> genRefArray[97][];
    1 -> kindArray[98]; 0 -> roomArray[98]; 0 -> sonArray[98]; 
    &referenceGenerator(# do &max[] -> as[] #)[] -> genRefArray[98][];
    1 -> kindArray[99]; 0 -> roomArray[99]; 0 -> sonArray[99]; 
    &referenceGenerator(# do &min[] -> as[] #)[] -> genRefArray[99][];
  #);
  &(# do
    1 -> kindArray[100]; 0 -> roomArray[100]; 0 -> sonArray[100]; 
    &referenceGenerator(# do &stdev[] -> as[] #)[] -> genRefArray[100][];
    1 -> kindArray[101]; 0 -> roomArray[101]; 0 -> sonArray[101]; 
    &referenceGenerator(# do &variance[] -> as[] #)[] -> genRefArray[101][];
    2 -> kindArray[102]; 2 -> roomArray[102]; 0 -> sonArray[102]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[102][];
    1 -> kindArray[103]; 0 -> roomArray[103]; 2 -> sonArray[103]; 
    &referenceGenerator(# do &funcOneRef[] -> as[] #)[] -> genRefArray[103][];
    1 -> kindArray[104]; 0 -> roomArray[104]; 4 -> sonArray[104]; 
    &referenceGenerator(# do &funcThreeRef[] -> as[] #)[] -> genRefArray[104][];
    2 -> kindArray[105]; 2 -> roomArray[105]; 0 -> sonArray[105]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[105][];
    1 -> kindArray[106]; 0 -> roomArray[106]; 0 -> sonArray[106]; 
    &referenceGenerator(# do &mod[] -> as[] #)[] -> genRefArray[106][];
    1 -> kindArray[107]; 0 -> roomArray[107]; 0 -> sonArray[107]; 
    &referenceGenerator(# do &sqrt[] -> as[] #)[] -> genRefArray[107][];
    1 -> kindArray[108]; 0 -> roomArray[108]; 0 -> sonArray[108]; 
    &referenceGenerator(# do &toChar[] -> as[] #)[] -> genRefArray[108][];
    1 -> kindArray[109]; 0 -> roomArray[109]; 0 -> sonArray[109]; 
    &referenceGenerator(# do &toNumber[] -> as[] #)[] -> genRefArray[109][];
    1 -> kindArray[110]; 0 -> roomArray[110]; 0 -> sonArray[110]; 
    &referenceGenerator(# do &length[] -> as[] #)[] -> genRefArray[110][];
    1 -> kindArray[111]; 0 -> roomArray[111]; 0 -> sonArray[111]; 
    &referenceGenerator(# do &round[] -> as[] #)[] -> genRefArray[111][];
    1 -> kindArray[112]; 0 -> roomArray[112]; 0 -> sonArray[112]; 
    &referenceGenerator(# do &trunc[] -> as[] #)[] -> genRefArray[112][];
    1 -> kindArray[113]; 0 -> roomArray[113]; 0 -> sonArray[113]; 
    &referenceGenerator(# do &abs[] -> as[] #)[] -> genRefArray[113][];
    1 -> kindArray[114]; 0 -> roomArray[114]; 0 -> sonArray[114]; 
    &referenceGenerator(# do &upper[] -> as[] #)[] -> genRefArray[114][];
    1 -> kindArray[115]; 0 -> roomArray[115]; 0 -> sonArray[115]; 
    &referenceGenerator(# do &lower[] -> as[] #)[] -> genRefArray[115][];
    1 -> kindArray[116]; 0 -> roomArray[116]; 0 -> sonArray[116]; 
    &referenceGenerator(# do &initCap[] -> as[] #)[] -> genRefArray[116][];
    2 -> kindArray[117]; 2 -> roomArray[117]; 0 -> sonArray[117]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[117][];
    1 -> kindArray[118]; 0 -> roomArray[118]; 0 -> sonArray[118]; 
    &referenceGenerator(# do &substr[] -> as[] #)[] -> genRefArray[118][];
    1 -> kindArray[119]; 0 -> roomArray[119]; 0 -> sonArray[119]; 
    &referenceGenerator(# do &bits[] -> as[] #)[] -> genRefArray[119][];
  #);
  &(# do
    1 -> kindArray[120]; 0 -> roomArray[120]; 1 -> sonArray[120]; 
    &referenceGenerator(# do &bracketedExpr[] -> as[] #)[] -> genRefArray[120][];
    1 -> kindArray[121]; 0 -> roomArray[121]; 1 -> sonArray[121]; 
    &referenceGenerator(# do &scalarName[] -> as[] #)[] -> genRefArray[121][];
    2 -> kindArray[122]; 2 -> roomArray[122]; 0 -> sonArray[122]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[122][];
    1 -> kindArray[123]; 0 -> roomArray[123]; 0 -> sonArray[123]; 
    &referenceGenerator(# do &eq[] -> as[] #)[] -> genRefArray[123][];
    1 -> kindArray[124]; 0 -> roomArray[124]; 0 -> sonArray[124]; 
    &referenceGenerator(# do &ne[] -> as[] #)[] -> genRefArray[124][];
    1 -> kindArray[125]; 0 -> roomArray[125]; 0 -> sonArray[125]; 
    &referenceGenerator(# do &lt[] -> as[] #)[] -> genRefArray[125][];
    1 -> kindArray[126]; 0 -> roomArray[126]; 0 -> sonArray[126]; 
    &referenceGenerator(# do &le[] -> as[] #)[] -> genRefArray[126][];
    1 -> kindArray[127]; 0 -> roomArray[127]; 0 -> sonArray[127]; 
    &referenceGenerator(# do &gt[] -> as[] #)[] -> genRefArray[127][];
    1 -> kindArray[128]; 0 -> roomArray[128]; 0 -> sonArray[128]; 
    &referenceGenerator(# do &ge[] -> as[] #)[] -> genRefArray[128][];
    2 -> kindArray[129]; 2 -> roomArray[129]; 0 -> sonArray[129]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[129][];
    1 -> kindArray[130]; 0 -> roomArray[130]; 1 -> sonArray[130]; 
    &referenceGenerator(# do &integerConstant[] -> as[] #)[] -> genRefArray[130][];
    1 -> kindArray[131]; 0 -> roomArray[131]; 2 -> sonArray[131]; 
    &referenceGenerator(# do &realConstant[] -> as[] #)[] -> genRefArray[131][];
    1 -> kindArray[132]; 0 -> roomArray[132]; 1 -> sonArray[132]; 
    &referenceGenerator(# do &stringConstant[] -> as[] #)[] -> genRefArray[132][];
    1 -> kindArray[133]; 0 -> roomArray[133]; 1 -> sonArray[133]; 
    &referenceGenerator(# do &inputParameter[] -> as[] #)[] -> genRefArray[133][];
    1 -> kindArray[134]; 0 -> roomArray[134]; 1 -> sonArray[134]; 
    &referenceGenerator(# do &tablename[] -> as[] #)[] -> genRefArray[134][];
    1 -> kindArray[135]; 0 -> roomArray[135]; 1 -> sonArray[135]; 
    &referenceGenerator(# do &alias[] -> as[] #)[] -> genRefArray[135][];
    2 -> kindArray[136]; 2 -> roomArray[136]; 0 -> sonArray[136]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[136][];
    1 -> kindArray[137]; 0 -> roomArray[137]; 2 -> sonArray[137]; 
    &referenceGenerator(# do &explicitTableName[] -> as[] #)[] -> genRefArray[137][];
    1 -> kindArray[138]; 0 -> roomArray[138]; 1 -> sonArray[138]; 
    &referenceGenerator(# do &implicitTableName[] -> as[] #)[] -> genRefArray[138][];
    2 -> kindArray[139]; 2 -> roomArray[139]; 0 -> sonArray[139]; 
    &referenceGenerator(# do &unExpanded[] -> as[] #)[] -> genRefArray[139][];
  #);
  &(# do
    1 -> kindArray[140]; 0 -> roomArray[140]; 0 -> sonArray[140]; 
    &referenceGenerator(# do &integerDouble[] -> as[] #)[] -> genRefArray[140][];
    1 -> kindArray[141]; 0 -> roomArray[141]; 0 -> sonArray[141]; 
    &referenceGenerator(# do &integerQuad[] -> as[] #)[] -> genRefArray[141][];
    1 -> kindArray[142]; 0 -> roomArray[142]; 0 -> sonArray[142]; 
    &referenceGenerator(# do &realQuad[] -> as[] #)[] -> genRefArray[142][];
    1 -> kindArray[143]; 0 -> roomArray[143]; 0 -> sonArray[143]; 
    &referenceGenerator(# do &realDoubleQuad[] -> as[] #)[] -> genRefArray[143][];
    1 -> kindArray[144]; 0 -> roomArray[144]; 1 -> sonArray[144]; 
    &referenceGenerator(# do &character[] -> as[] #)[] -> genRefArray[144][];
    1 -> kindArray[145]; 0 -> roomArray[145]; 1 -> sonArray[145]; 
    &referenceGenerator(# do &numeric[] -> as[] #)[] -> genRefArray[145][];
    1 -> kindArray[146]; 0 -> roomArray[146]; 2 -> sonArray[146]; 
    &referenceGenerator(# do &bcd[] -> as[] #)[] -> genRefArray[146][];
    1 -> kindArray[147]; 0 -> roomArray[147]; 1 -> sonArray[147]; 
    &referenceGenerator(# do &displayString[] -> as[] #)[] -> genRefArray[147][];
    1 -> kindArray[148]; 0 -> roomArray[148]; 1 -> sonArray[148]; 
    &referenceGenerator(# do &columnInteger[] -> as[] #)[] -> genRefArray[148][];
    1 -> kindArray[149]; 0 -> roomArray[149]; 1 -> sonArray[149]; 
    &referenceGenerator(# do &columnIdName[] -> as[] #)[] -> genRefArray[149][];
    1 -> kindArray[150]; 0 -> roomArray[150]; 1 -> sonArray[150]; 
    &referenceGenerator(# do &columnIdString[] -> as[] #)[] -> genRefArray[150][];
  #)
#);

#); 
