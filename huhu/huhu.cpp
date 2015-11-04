// huhu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("\n%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n\n");
   return 0;
}

int main(int argc, char* argv[])
{
  sqlite3 *db;
   char *zErrMsg = 0;
   int rc,rc1,rc2,rc3,rc4;
   char *sql,*sql1,*sql2,*sql3,*sql4;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("C:\\sqlite\\41.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      //exit(0);
   }else{
      fprintf(stderr, "Opened database successfully!\n\n");
   }

 /* Create merged SQL statement */
    //sql="insert into test(SBD,Diemtb1,Hoa) SELECT SBD, ((Toan*2+Ly+Hoa)/4 +(KV+DT)/3 + UT) as Diemtb1, Hoa from tonghop where NV1N ='KT11' ";
   // sql1="insert into test1(SBD,Diemtb2,Anh) SELECT SBD, ((Toan*2+Ly+Anh)/4 +(KV+DT)/3 + UT) as Diemtb2, Anh from tonghop where NV1N ='KT11'  ";
    //sql2="insert into test3(SBD,nvso,manv,Diemtb) select test.SBD, 1 as nvso, 'KT11' as manv, case when (Diemtb1>=Diemtb2) then Diemtb1 else Diemtb2 end as Diemtb from test, test1 where test.SBD=test1.SBD and Diemtb>=6.0";
	//sql3="insert into nvxt(sbd,nvso,manv,diemxt) select SBD as sbd, nvso as nvso, manv as manv, Diemtb as diemxt from test3 order by Diemtb DESC limit 200"; 
	sql4="insert into nvxt(sbd,nvso,manv,diemxt) select SBD as sbd, nvso as nvso, manv as manv, Diemtb as diemxt from test3  where Diemtb =( select diemxt from nvxt order by diemxt ASC limit 1) and SBD not in( select sbd from nvxt)"; 
	/* Execute SQL statement */
   //rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
  // rc1 = sqlite3_exec(db, sql1, callback, (void*)data, &zErrMsg);
   //rc2 = sqlite3_exec(db, sql2, callback, (void*)data, &zErrMsg);
	// rc3 = sqlite3_exec(db, sql3, callback, (void*)data, &zErrMsg);
    rc4 = sqlite3_exec(db, sql4, callback, (void*)data, &zErrMsg);
   if( rc3 != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully!\n\n");
   }

   sqlite3_close(db);

   return 0;
}