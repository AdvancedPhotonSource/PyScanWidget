
import sys
import json
import time
import signal
import sys

global variableDict
variableDict = {'Start_Pos': 0.0, 
				'Step_Size': 1.0,
				'my_arr': '1.1,2.2,3.3',
				'End_Pos':2.0,
				'TestString': 'stringStuff'
				}

def getVariableDict():
	return variableDict

def signal_handler(signal, frame):
		print ('sigint')
		sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def update_variable_dict():
	global variableDict
	argDic = {}
	if len(sys.argv) > 1:
		strArgv = sys.argv[1]
		argDic = json.loads(strArgv)
	print ('orig variable dict', variableDict)
	for k,v in argDic.items():
		variableDict[k] = v
	print ('new variable dict', variableDict)


def start_scan():
	print ('running scan')
	time.sleep(10)
	print ('finished scan')


def main():
	update_variable_dict()
	f_arr = [float(x) for x in variableDict['my_arr'].split(',') ]
	print ('farray', f_arr)
	print (variableDict)
	start_scan()


if __name__ == '__main__':
	main()

