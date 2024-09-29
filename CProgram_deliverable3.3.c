// Include this library to be able to make calls in shiva2.upc.es
// #include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Structure for storing query results
	MYSQL_RES *result;
	MYSQL_ROW row;
	// Connection to the MYSQL server
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf("Error while trying to set connection: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Initialize the connection
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "League",0, NULL, 0);
	if (conn==NULL) {
		printf("Error while trying to initialize the connection: %u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	char GameID[20];
	// I ask the username of a player
	printf("Insert the Game ID to obtain the usernames of the players involved in the game:");
	scanf("%s", GameID);
	char query[256];
	strcpy(query, "SELECT DISTINCT Player.Username FROM Player, Game, Game_Record WHERE Player.Identifier_P = Game_Record.Player AND Game_Record.Game = '");
	strcat(query, GameID);
	strcat(query, "'");
	
	err=mysql_query (conn, query);
	if (err!=0) {
		printf ("Error while processing the query request from database %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// We collect the result of the query. The result of the
	// query is returned in a variable of pointer type to
	// MYSQL_RES as we have declared previously.
	// This is a virtual table in memory that is the copy
	// from the actual table on disk.
	result = mysql_store_result(conn);
	// The result is a matrix structure in memory
	// where each row contains data for one person.
	
	// Now we get the first row that is stored in a
	// variable of type MYSQL_ROW
	row = mysql_fetch_row(result);
	if (row == NULL)
		printf("An empty set of data was obtained while doing the query\n");
	else
		while (row !=NULL) {
			// Column 0 contains the player's name
			printf("%s\n", row[0]);
			// Get the next row
			row = mysql_fetch_row(result);
	}
		mysql_close(conn);
		exit(0);
}