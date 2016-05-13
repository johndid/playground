#!/usr/bin/env python

import re
import optparse
import os
import sqlite3
import sys

def createQuery(db):
    try:
        conn = sqlite3.connect(db,detect_types=sqlite3.PARSE_DECLTYPES)
        conn.row_factory = sqlite3.Row
        query = conn.cursor()
        return query
    
    except Exception, e:
        print "Exception: " + str(e)
        if 'encrypted' in str(e):
            print 'Error: reading cookies database: ' + str(db)
    return null

def printTables(file):
    try:
        query = createQuery(file)
        query.execute("SELECT name FROM sqlite_master WHERE type='table';")
        tables = query.fetchall()
        print "file: " + os.path.basename(file)
        for table in tables:
            printTable(query,table[0])
    except Exception, e:
        print "Exception: " + str(e)
        if 'encrypted' in str(e):
            print 'Error: reading cookies database. Please upgrade your Python-Sqlite3 Library'
            exit(0)

def printTable(query,table):
    try:
        query.execute("SELECT * FROM " + table + ";")

        keys = query.fetchone()
        if keys is None:
            print "table: " + str(table) + " row: None count: " + str(len(query.fetchall()))
        else:
            print "table: " + str(table) + " row: " + str(keys.keys()) + " count: " + str(len(query.fetchall()))

        query.execute("SELECT * FROM " + table + ";")
        rows = query.fetchall()
        i=0;
        for row in rows:
            print "table: " + str(table) + " row[" + str(i) + "] " + str(dict(row))
            i+=1
            
    except Exception, e:
        print "Error: Exception thrown: " + str(e)
        
# def printCookies(query,table):
#     try:
#         query.execute('SELECT host, name, value FROM ' + table +';')
#         for row in query:
#             host = str(row[0])
#             name = str(row[1])
#             value = str(row[2])
#             print '[+] Cookie -> Host: ' + host + ' Cookie: ' + name + ' Value: ' + value
#     except Exception, e:
#         print "[!] Exception: " + str(e)
#         if 'encrypted' in str(e):
#             print '\n[*] Error reading cookies database'
#             print '[*] Upgrade your Python-Sqlite3 Library'
#             exit(0)
#         else:
#             print '\n[*] No Cookies found in: ' + str(db)

# def printDownloads(db):
#     conn = sqlite3.connection(db)
#     query = conn.cursor()
#     query.execute('SELECT name, source, datetime/endTime/100000,\'unixepoc\') FROM moz_downloads;')
#     print '\n[*] --- Firefox Downloads ---'
#     for row in query:
#         print '[+] File: '+ str(row[0]) + ' from source: ' + str(row[1]) + ' at: ' + str(row[2])

# def printHistory(db):
#     try:
#         conn = sqlite3.connection(db)
#         query = conn.cursor()
#         query.execute('SELECT url, datetime(visit_date/100000,\'unixepoch\') FROM moz_places,moz_historyvisits WHERE visit_count >0 and moz_places.id == moz_history_visits.place_id;')
#         print '\n[*] --- Firefox History ---'
#         for row in query:
#             url = str(row[0])
#             date = str(row[1])
#             print '[+] ' + date + ' Visited: ' + url
#     except Exception, e:
#         if 'encrypted' in str(e):
#             print '\n[*] Error reading your places database'
#             print '[*] Upgrade your Python-Sqlite3 Library'
#             exit(0)

# def printGoogle(db):
#     try:
#         conn = sqlite3.connection(db)
#         query = conn.cursor()
#         query.execute('SELECT url, datetime(visit_date/100000,\'unixepoch\') FROM moz_places,moz_historyvisits WHERE visit_count >0 and moz_places.id == moz_history_visits.place_id;')
#         print '\n[*] --- Firefox Google searches --- '
#         for row in query:
#             url = str(row[0])
#             date = str(row[1])
#             if 'google' in url.lower():
#                 r = re.findall(r'q=.*\&',url)
#                 if r:
#                     search = r[0].split('&')[0]
#                     search = search.replace('q=','').replace('+',' ')
#                     print '[+] ' + date + ' Searched for: ' + search
#     except Exception, e:
#         if 'encrypted' in str(e):
#             print '\n[*] Error reading your places database'
#             print '[*] Upgrade your Python-Sqlite3 Library'
#             exit(0)
def printFile(file):
    if os.path.isfile(file):
        printTables(file)
    else:
        print "Error: file: " + file + " Does not exist?"

def optionTable(option, opt_str, value, parser):
    printFile(value)
    
def optionList(option, opt_str, value, parser):
    # NOTICE: There will be an single empty line passed from the generated `xargs -0` list.
    # This empty file name must to be removed. Hence the 'if len()' check below
    files=re.split('\n',value) 
    for file in files:
        if len(file):
            printFile(file)

def printList(files):
    for file in files:
        if len(file):
            printFile(file)

def main():
    parser = optparse.OptionParser(version="%prog 0.1")
    parser.add_option('-v', action='store_true', dest='verbose', help='Verbose mode, dumps contents of SQLite 3 databases')
    parser.add_option('-l', action='callback', dest='list', type='string', callback=optionList, help='List of paths to SQLite 3 database files created with "find command | xargs -0" (a list seperated by newlines not spaces!)')
    parser.set_defaults(verbose=False)
    (options, args) = parser.parse_args()

    # see this dick wipe construction dosen't work! Why? because the bloody function is called before the final variable assignment
    # is set, so the verbose option will never be set!
    # so with this construction there can be noooooooooo easy function calling!
#    global verbose
#    verbose=options.verbose

    #todo ensure that calling program with only verbose throws an error!
    #if len(sys.argv) is 1: #does not work. Hence args=0 after the parsing an none are stored in the add_option therefore the error is thrown
    #if len(args) <= 1: # see above
    if len(sys.argv) is 1:
        parser.error("wrong number of arguments")
        exit(-1)

if __name__ == '__main__':
    main()
