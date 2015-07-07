#
# define compiler and compiler flag variables
#
#JFLAGS = -g -classpath .
JFLAGS = -g 
JC = javac 

#
# Target entry for creating .class files from .java files 
#
.SUFFIXES: .java .class

# This is a target entry that uses the suffix rule syntax:
#	DSTS:
#		rule
#  'TS' is the suffix of the target file, 'DS' is the suffix of the dependency 
#  file, and 'rule'  is the rule for building a target	
# '$*' is a built-in macro that gets the basename of the current target 
# Remember that there must be a < tab > before the command line ('rule') 
#
.java.class:
	$(JC) $(JFLAGS) $*.java

#
# CLASSES is a macro symbol consisting of our source files
#
CLASSES = \
	Sequence.java \
	Sort.java \
	BubbleSort.java \
	QuickSort.java \
	SelectionSort.java \
	ShellSort.java \
	InsertionSort.java \
	SortDemoSequence.java \
	TextSequence.java \
	SortDemo.java \
	SortText.java \
	RandomString.java

#
# the default make target entry
#
default: classes

#
# This target entry uses Suffix Replacement within a macro: 
# $(name:string1=string2)
# 	In the words in the macro named 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .java of all words in the macro CLASSES 
# with the .class suffix
#
classes: $(CLASSES:.java=.class)

#
# RM is a predefined macro in make (RM = rm -f)
#
clean:
	$(RM) *.class


