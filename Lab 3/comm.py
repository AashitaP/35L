import random, sys
from optparse import OptionParser

class compare:
	def __init__(self, filename1, filename2):
		if filename1 == '-':
			self.lines1 = sys.stdin.readlines()
		else:
			f = open(filename1, 'r')
			self.lines1 = f.readlines()
			f.close()
		if filename2 == '-':
			self.lines2 = sys.stdin.readlines()
		else:
			f = open(filename2, 'r')
			self.lines2 = f.readlines()
			f.close()

def main():
	version_msg = "%prog 2.0"
	usage_msg = """%prog [OPTION] ... FILE1 FILE2

Output comparison of FILE1 and FILE2."""

	parser = OptionParser(version = version_msg, usage = usage_msg)
	parser.add_option("-1", action="store_true", dest="col1", help= "hide the 1st column", default=False)
	parser.add_option("-2", action ="store_true", dest="col2", help="hide the 2nd column", default=False)
	parser.add_option("-3", action="store_true", dest="col3", help="hide the 3rd column", default=False)
	parser.add_option("-u", action="store_true", dest="unsorted", default=False, help="compare unsorted files")

	(options, args) = parser.parse_args() #uses sys.argv[1:] by default

	if len(args) != 2:
		parser.error("wrong number of input operands")

	input_file1 = args[0]
	input_file2 = args[1]
	cols = []

	try:
		comm = compare(input_file1, input_file2)
	except:
		parser.error("cannot compare files {0} and {1}". 
						format(input_file1, input_file2))

	try:
		if options.unsorted == False:
			index1 = 0
			index2 = 0
			while index1 < len(comm.lines1) and index2 < len(comm.lines2):
				if (comm.lines1[index1] == comm.lines2[index2]):
					cols.append([comm.lines1[index1], 3]) #we are making a list of 2 element lists, the second element stats which column it belongs in
					index1 += 1
					index2 += 1
				elif (comm.lines1[index1] < comm.lines2[index2]):
					cols.append([comm.lines1[index1], 1])
					index1 += 1
				else:
					cols.append([comm.lines2[index2], 2])
					index2 += 1
			if index1 < len(comm.lines1): #if one list finishes first, append the rest of the other
				while index1 < len(comm.lines1):
					cols.append([comm.lines1[index1], 1])
					index1 += 1
			elif index2 < len(comm.lines2):
				while index2 < len(comm.lines2):
					cols.append([comm.lines2[index2], 2])
					index2 += 1
	except:
		parser.error("comparison of sorted files failed")

	try:
		if options.unsorted: #for files with -u flag set
			for line1 in comm.lines1:
				repeated = False
				for line2 in comm.lines2:
					if line1 == line2:
						cols.append([line1, 3])
						comm.lines2.remove(line2)
						repeated = True
						break #break inner loop
				#second loop ended, i.e. no repeatition found
				if repeated == False:
					cols.append([line1, 1])
			for line2 in comm.lines2:
				cols.append([line2, 2])
	except:
		parser.error("comparison of unsorted files failed")


	for i in cols:
		if i[1] == 1:
			if options.col1 == False:
				sys.stdout.write(i[0])
		elif i[1] == 2:
			if options.col2 == False:
				if options.col1 == True:
					sys.stdout.write(i[0])
				else:
					sys.stdout.write('\t' + i[0]) 
		elif i[1] == 3:
			if options.col3 == False:
				if options.col1 == False and options.col2 == False:
					sys.stdout.write('\t\t' + i[0])
				elif options.col1 == False and options.col2 == True:
					sys.stdout.write('\t' + i[0])
				elif options.col1 == True and options.col2 == False:
					sys.stdout.write('\t' + i[0])
				else:
					sys.stdout.write(i[0])
	
	#if options.col1 == False or options.col2 == False or options.col3 == False:
	#	sys.stdout.write('\n')
if __name__ == "__main__":
	main()

