#!/usr/bin/python

import os, sys
import fnmatch
import subprocess
import filecmp

def testCode( retcode, msg ):
    if retcode > 0:
        print msg
        sys.exit( 1 )

testDir = os.path.join( os.getcwd(), 'cases')
if not os.path.isdir( testDir ):
    print testDir, "isn't a directory"
    sys.exit( 1 )

executable = os.path.join(os.getcwd(), "run")
if not os.path.isfile( executable ):
    retcode = subprocess.call("make",shell=True)
    testCode( retcode, "\tFAILED to make the scanner" )


def resultMatch(infile, outfile):
    retcode = subprocess.call("python -m mccabe "+infile+">"+outfile, shell=True)
    fileTmp = open(output, 'r')
    program = fileTmp.readlines()
    fileTmp.close()
    tmp = {}
    for line in program:
        if ':' in line:
            lineno = int(line[2:int(line.find(':'))])
        else:
            lineno = int(line[int(line.find(' ')):int(line.find(','))-1])
        tmp[lineno] = line

    fileTmp = open(output, 'w')
    for key in sorted(tmp):
        fileTmp.write(tmp[key])
    fileTmp.close()



files = os.listdir( testDir )
for x in files:
    if fnmatch.fnmatch(x, "*.py"):
        testcase = os.path.join(testDir, x)
        output = testcase[:-3]+".out"
        resultMatch(testcase, output)

        retcode = subprocess.call("./run < "+testcase+"> ./tmp/out",shell=True)
        if retcode != 0:
            testCode( retcode, "\tFAILED to run test case "+x)
        else:
            if not os.path.isfile( output ):
                print "test case", x[:-3]+'.out', "doesn't exist"
                sys.exit( 1 )
            if not filecmp.cmp("./tmp/out", output): 
                print "\tTEST CASE FAILED", x
            else :
                print "testcase:", x, "passed"

