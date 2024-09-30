#User can change these settings accordingly if they wish to change the number of characters in a string or the number of strings
.set $Nstrings, 3 #the number of bitstrings you want to enter
.set $Nbits, 35 # The number of bits/characters/ zeroes and ones, one bitstring should consist of
.set $NbitsMin, 34 #Previous answer minus one for simplicity in the code
.set $Nbytes,5 #Nbits divided by 8 rounded up. 

#Code settings
.set $One, 1 #For simplicity in the code, since we want to add or subtract one often.
.data
	askBitstring:		.align 2
						.string "\nEnter bitstring " 
	continueAsk:		.align 2
						.string " consisting of "
	finishAskBitstring:	.align 2
						.string " bits and press enter:"
	printBitstring: 	.align 2
						.string "Check: the string filled in and accessed is: "
	printTotal:			.align 2
						.string "\nThe total hamming distance is: "
	printAverage:		.align 2
						.string "\nThe integer part of the average hamming distance is: "
	printRemainder:		.align 2
						.string "\nThe remainder part of the average hamming distance is: "
	printCombinations:	.align 2
						.string "\nOf the total number of unique pairs:"
	offNewBitstrAddr:	.align 2
						.word 0
	firstBitstringAddr: .align 2
						.space 1   # declaring space for input string
	


.text
#NOTE I use MUL instead of MULT, that only receives the lower part, we assume no overflow will occur
#We could fix that by using mult, then mflo to move the result from lo to a register, and check with mfhi, if the value
#in hi >0, if so, we have overflow

#NOTE We assume the user fills in a bitstring at least the size specified in the print statement!!
.global _start												# Let the program know we have to start at label main

_start:
	li		$s0, 1 #Define a counter to keep track of which bitstring needs to be entered
	li		$s7,0 #Define a counter to keep track of the number of pairs we compare
	#start to calculate the offset and save the result in at adress offNewBitstAddr
	li 		$t0, $Nbytes
	li		$t1, 8 #8 bits in a byte
	mul		$t0, $t0, $t1 # number of bits used
	sw		$t0, offNewBitstrAddr 
	# jump to next part to define bitstrings
	li		$s5, 0 # here we will store the total hamming distance
	li 		$s6, 0 # here we will store the average hamming distance
	j AskUserInput

AskUserInput:
	#Ask the user to enter the bitstring
	la		$a0,askBitstring		# Load the address of the question to enter the bitstring
	li		$v0,4                 # Initiate that we want to print a string
	syscall						# making a system call to print the string
	
	#print the bitstring number that needs to be entered
	li 		$v0, 1 					#initiate that we want to print an integer
	add		$a0,$0, $s0 			#load the number of the bitstring to be printed in a0
	syscall
	
	#continue the question
	la		$a0,continueAsk        # Load the address of the question to enter the bitstring
	li		$v0,4                  # Initiate that we want to print a string
	syscall	
	
	#Print the number of bytes needed
	li		$v0, 1
	li		$a0,$Nbits
	syscall
	
	#finish the sententce
	la		$a0,finishAskBitstring              # Load the address of the last part of the question
	li		$v0,4                               # Initiate that we want to print a string
	syscall
	
	# Let the user fill in the strings
	#First define the address in a0:
	
	sub		$t0, $s0,$One #our factor
	lw		$t1, offNewBitstrAddr #load the basic offset in t1
	mul 	$t1, $t1, $t0 #calculate the specific offset
	
	li 		$a1, $Nbits
	add		$a1, $a1,$One		# Specify the length of the bitstring we save (+1)
	addi	$a0, $t1, firstBitstringAddr		# add the offset to our initial address              
	move	$t1, $a0                           	# loading address of input string into a register
	li		$v0,8 								# Initiate that we want to read a string
	syscall									# Syscall to actually read the string
 
	#print string input confirmation
	la 		$a0, printBitstring
	li 		$v0, 4
	syscall

	li 		$v0, 4						#Initiate that we want to print the saved string
	move 	$a0, $t1					#move the bitstring address to a0 to print it
	syscall
	
	#jump to the next part when all bitstrings are defined
	li		$t2, $Nstrings #to branch based on the number of strings after saving these strings we use if for smt else
	beq 	$s0, $t2, CalcTotalHamm
	#if we did not take the branch, we have to ask the user again for a bitstring,so go back to the top
	# after incrementing s0
	addi 	$s0, $s0, $One
	j AskUserInput
	

  
CalcTotalHamm:
	# loop over strings and calc hamming distance (part of Guusje and Elise needs to be combined here)
	#Use s0 to keep track of the counter of the first bitstring we want to compare
	#Use s1 keep track of the counter of the second bitstring we want to compare each loop
	li 		$s0, -1
	j SelectFirstToCompare
	
	SelectFirstToCompare:
		li		$t5, 1
		add 	$s0, $s0, $t5
		li 		$t0, $Nstrings
		li		$t5, -1
		add 	$t0, $t0, $t5
		beq 	$s0, $t0, DoneSoPrintResults
		#If we haven't reached the last bit yet, jump to select second
		li		$t5, 0
		add 	$s1, $s0,$t5
		j SelectSecondToCompare

		SelectSecondToCompare:
			#select the second bitstring to compare
			li		$t5,1
			add 	$s1, $s1, $t5
			beq 	$s1, $Nstrings, SelectFirstToCompare
			#If we don't branch, meaning that we have two different strings we want to compare, we want to calc the hamm dist
			j CalcHammPair
			
CalcHammPair:
	#first update the counter of comared pairs:
	li		$t5, 1
	add 	$s7, $s7, $t5
	#Start by calculating the starting addresses in memory where each bitstring starts
	#Since we now count from zero, we have our factor at $s0, to calculate the address of the first bitstring at s2	
	lw		$t0, offNewBitstrAddr #load the basic offset in t1
	mul 	$t0, $t0, $s0 #calculate the specific offset
	li		$t5, firstBitstringAddr
	add		$s2, $t0, $t5		# add the offset to our initial address              
	
	#Since we now count from zero, we have our factor at $s1, to calculate the address of the first bitstring at s3	
	lw		$t0, offNewBitstrAddr #load the basic offset in t1
	mul 	$t0, $t0, $s1 #calculate the specific offset
	li		$t5, firstBitstringAddr
	add		$s3, $t0, $t5		# add the offset to our initial address              
	
	#Now the address of bitstring1 is in s2, and the address of bitstring2 is in s3
	#Use these to calculate the hamming distance
	li 		$t6, 0 # this is a counter for the string size
	LoopOverBytes:
		beq		$t6, $Nbits, SelectSecondToCompare
		add		$t3, $s2, $t6
		add		$t4, $s3, $t6
		lb		$t7, 0($t3)
		lb		$t8, 0($t4)
		beq		$t7, $t8, DontAdd
		li		$t5, 1
		add		$s5, $s5, $t5
		DontAdd:
		li		$t5, 1
		add 	$t6, $t6, $t5
		j		LoopOverBytes



DoneSoPrintResults:
	#code to run after we have looped over all possible pairs and summed up the hamming distances
	
	# Print the total hamming distance
	la 		$a0, printTotal
	li 		$v0, 4
	syscall

	li 		$v0, 1						#Initiate that we want to print the total hamming dist string
	move 	$a0, $s5					#move the total hamming dist to a0 to print it
	syscall
	
	# calculate the average hamming distance, in $s5 is the total hamming dist, s7 the number of pairs
	div 	$s5, $s7
	mflo 	$t1 #t1 contains the integer part of the average
	mfhi 	$t2 #t2 contains the remainder of the average

	
	
	# Print the integer part of the average hamming distance
	la 		$a0, printAverage
	li 		$v0, 4
	syscall

	li 		$v0, 1						#Initiate that we want to print the integer part of the average hamming dist string
	move 	$a0, $t1					#move the int part to to a0 to print it
	syscall
	
	#print the remainder
	la 		$a0, printRemainder
	li 		$v0, 4
	syscall
	
	li 		$v0, 1						#Initiate that we want to print the remainder part of the average hamming dist string
	move 	$a0, $t2					#move the remainder to a0 to print it
	syscall

	#print the total number of combinations
	la 		$a0, printCombinations
	li 		$v0, 4
	syscall
	
	li 		$v0, 1						#Initiate that we want to print the total number of possible pairs
	move 	$a0, $s7					#move the number of pairs to a0 to print it
	syscall
	
	#End the simulation part
	j Exit

Exit:
    li		$v0, 10
    syscall