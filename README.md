# QT MQTT Database Interface

This provides a mechanism to get DB data via JSON from a MySQL database. Theory says it could be used by applications that you don't want to have direct access to the MySQL credentials and connection details.

## How it works
It's a simple JSON and MQTT based API. All API calls are to database/request and all return values are to database/response. Clients should subscribe to database/response/# and check topic names for specific replies. All request API calls can include an identifier to allow for quickly parsing any response to associate with a request.

The ident string is a freeform string consisting of uppercase, lowercase, and digits. It cannot contain special characters. It has a max length of 64 characters.

The server will ignore any query that isn't a SELECT as this is a read only interface. You cannot store or delete data on the database through this interface.

All API calls are MQTT topics, and the payload would be JSON based key/value pairs.

## Get available databases

```
topic: database/request/databaselist
payload: {"ident":"string"}
```

Will return 

```
topic: database/response/databaselist
payload: 
{
    "ident":"string",
    "databases": [
        "name",
        "name",
        "...",
    ]
}
```

If databases array is empty, either no databases exist, the server isn't connected, or the server doesn't have permissions to read them.

## Get tables for a database

```
topic: database/request/tablelist
payload: {"ident":"string", "database":"database name"}
```

Will return

```
topic: database/response/tablelist
payload:
{
    "ident":"string",
    "tables": [
        "name",
        "name",
        "...",
    ]
}
```

If the tables array is empty, either no tables exist, the database name was not valid, or the server doesn't have permission to read them.

## Get table field names

```
topic: database/request/tablefieldnames
payload: {"ident":"string","database":"database name","table":"table name"}
```

Will return
```
topic: database/response/tablefieldnames
payload:
{
    "ident":"string",
    "fields":[
        "fieldname",
        "fieldname",
        "...",
    ]
}
```

If the fields array is empty, either the table is empty, the table or database names were not valid, or the server doesn't have permission to read them.

## Get all table data

## Get table data based on a SELECT query


