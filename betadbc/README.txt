README for BetaDBC 
------------------

This library contains the source for an ODBC compliant interface to
relational databases.

The tutorial/ directory contains programs showing the
most important functionality.

Currently the implementation only runs on Windows and Unix.

TYPE CONSIDERATIONS
-------------------

The following conversions of types are considered to be right.  (Any
type can though be converted to a text. Other conversion may be
attempted with unpredictable results :-) )

Typical SQL Type		BETA Type or Class
--------------------------------------------------
CHAR(n)				text	
VARCHAR(n)			text	
LONG VARCHAR			text
DECIMAL(p,s)			text
NUMERIC(p,s)			text
SMALLINT			shortint
INTEGER				integer
REAL				real [There is no single precision float type in BETA]
FLOAT(p)			real 
DOUBLE PRECISION		real
BOOLEAN				boolean 
TINYINT				char
BIGINT				text
BINARY(n)			text
VARBINARY(n)			text
LONG VARBINARY			text
DATE				time [As in ~beta/basiclib/current/timedate,
				      Considering the year, month, day attr.]  
TIME				time [Considering the hour,minute,sec,
attr.] 
TIMESTAMP			time [Considering the year, month,
day, hour, minute, sec attr.]



DON'T READ BELOW THIS LINE :-)
------------------------------

TYPE CONSIDERATIONS FOR INTERNAL USE
------------------------------------

C Type Identifier	Odbc C Typedef		C Type
--------------------------------------------------------------------------------------------
SQL_C_CHAR		SQLCHAR *		unsigned char *
SQL_C_SSHORT [j]	SQLSMALLINT		short int
SQL_C_USHORT [j]	SQLUSMALLINT		unsigned short int
SQL_C_SLONG [j]		SQLINTEGER		long int
SQL_C_ULONG [j]		SQLUINTEGER		unsigned long int
SQL_C_FLOAT		SQLREAL			float
SQL_C_DOUBLE		SQLDOUBLE, SQLFLOAT	double
SQL_C_BIT		SQLCHAR			unsigned char
SQL_C_STINYINT [j]	SQLSCHAR		signed char
SQL_C_UTINYINT [j]	SQLCHAR			unsigned char
SQL_C_SBIGINT		SQLBIGINT		_int64 [h]	
SQL_C_UBIGINT		SQLUBIGINT		unsigned _int64 [h]
SQL_C_BINARY		SQLCHAR	*		unsigned char *
SQL_C_BOOKMARK [i]	BOOKMARK		unsigned long int [d]
SQL_C_VAR-BOOKMARK	SQLCHAR *		unsigned char *
SQL_C_TYPE_DATE [c]	SQL_DATE_STRUCT		struct tagDATE_STRUCT {
							SQLSMALLINT year; 
							SQLUINTEGER month; 
							SQLUINTEGER day; 
						} DATE_STRUCT; [a]
SQL_C_ TYPE_TIME [c]	SQL_TIME_STRUCT		struct tagTIME_STRUCT {
							SQLUSMALLINT hour; 
							SQLUSMALLINT minute; 
							SQLUSMALLINT second; 
						} TIME_STRUCT; [a]
SQL_C_ TYPE_TIMESTAMP	SQL_TIMESTAMP_		struct tag TIMESTAMP_STRUCT {
[c]			STRUCT			SQLSMALLINT year; 	
							SQLUSMALLINT month; 
							SQLUSMALLINT day; 
							SQLUSMALLINT hour; 
							SQLUSMALLINT minute; 
							SQLUSMALLINT second; 
							SQLUINTEGER fraction; [b]
						} TIMESTAMP_STRUCT; [a]
SQL_C_NUMERIC		SQL_NUMERIC_		struct tag SQL_NUMERIC_STRUCT {
			STRUCT				SQLCHAR precision;
							SQLSCHAR scale; 
							SQLCHAR sign [g]; 
							SQLCHAR
							val[SQL_MAX_NUMERIC_LEN]; [e], [f] 
						} SQL_NUMERIC_STRUCT;
SQL_C_INTERVAL_YEAR	SQL_INTERVAL_STRUCT
SQL_C_INTERVAL_MONTH
SQL_C_INTERVAL_DAY
SQL_C_INTERVAL_HOUR
SQL_C_INTERVAL_MINUTE
SQL_C_INTERVAL_SECOND
SQL_C_INTERVAL_YEAR_TO_MONTH
SQL_C_INTERVAL_DAY_TO_HOUR
SQL_C_INTERVAL_DAY_TO_MINUTE
SQL_C_INTERVAL_DAY_TO_SECOND
SQL_C_INTERVAL_HOUR_TO_MINUTE
SQL_C_INTERVAL_HOUR_TO_MINUTE
SQL_C_INTERVAL_HOUR_TO_SECOND
SQL_C_INTERVAL_HOUR_TO_SECOND
SQL_C_INTERVAL_MINUTE_TO_SECOND









