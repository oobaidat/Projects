import random
import time

def arthmetic(operation, number1, number2):
    match operation:
        case "+":
            answer = number1 + number2
        case "-":
            answer = number1 - number2
        case "*":
            answer = number1 * number2
        case "/":
            answer = number1 / number2
    return answer

# difficulty will be between 1 and 15
def generate_question(difficulty):
    # easy
    if difficulty <= 5:
        # generate 3 numbers of 1 digit
        number1 = random.choice(range(0, 10))
        number2 = random.choice(range(0, 10))
        number3 = random.choice(range(0,10))
    # medium
    elif difficulty <= 10:
        # generate 3 numbers of 2 digits
        number1 = random.choice(range(0, 100))
        number2 = random.choice(range(0, 100))
        number3 = random.choice(range(0,100))
    # hard
    else:
        # generate 3 numbers of 3 digits
        number1 = random.choice(range(0, 1000))
        number2 = random.choice(range(0, 1000))
        number3 = random.choice(range(0,1000))

    # initialised operation2 as empty for a check later
    operation2 = ""

    # with increase in dificulty we increase number of operations
    # assumption that *,/ are always harder than +,-
    if difficulty % 5 == 1: 
        operations = ["+", "-"]
        operation1 = random.choice(operations)
    elif difficulty % 5 == 2:
        operations = ["*", "/"]
        operation1 = random.choice(operations)
    elif difficulty % 5 == 3:
        operations = ["+", "-"]
        operation1 = random.choice(operations)
        operation2 = random.choice(operations)
    elif difficulty % 5 == 4:
        operations1 = ["*", "/"]
        operations2 = ["+", "-"]
        # make sure operation1 is *,/ so we follow bedmas
        operation1 = random.choice(operations1)
        operation2 = random.choice(operations2)

    else:
        operations = ["*", "/"]
        operation1 = random.choice(operations)
        operation2 = random.choice(operations)

    # make sure we don't divide by 0
    if number2 == 0 and operation1 == "/":
        if difficulty <= 5:
            number2 = random.choice(range(1, 10))
        elif difficulty <= 10:
            number2 = random.choice(range(1, 100))
        else:
            number2 = random.choice(range(1, 1000))

    answer = arthmetic(operation1, number1, number2)
    equation = f"{number1} {operation1} {number2}"

    # checks whether or not we need to do another operation
    if operation2 != "":
        if number3 == 0 and operation2 == "/":
            if difficulty <= 5:
                number3 = random.choice(range(1, 10))
            elif difficulty <= 10:
                number3 = random.choice(range(1, 100))
            else:
                number3 = random.choice(range(1, 1000))
        answer = arthmetic(operation2, answer, number3)
        equation = f"{number1} {operation1} {number2} {operation2} {number3}" 

    return equation, answer

def get_answer(qAnswer, hints, wrong):
    # make sure input from user is either a number or "y" if they want a hint
    while True:
        try:
            answer = input("What is your answer? ")
            # hint is to give the answer digit by digit
            # user can ask for a hint only after answering wrong at least once
            if answer == "y" and wrong != 0:
                hints += 1
                if hints >= len(qAnswer):
                    print(f"Hint: The answer is {qAnswer}")
                    hints = len(qAnswer)
                elif qAnswer[0] == "-" and hints == 1:
                    print(f"Hint: The answer is a negative number")
                # elif qAnswer[0] == "0" and qAnswer[1] == "." and hints == 1:
                #     print(f"Hint: The answer is a decimal number")
                else:
                    if qAnswer[0] == "-":
                        print(f"Hint: First {hints - 1} digit(s) of the answer: {qAnswer[:hints]}")
                    elif qAnswer[0] == "0" and qAnswer[1] == ".":
                        print(f"Hint: First {hints - 1} digit(s) of the answer: {qAnswer[:hints+1]}")
                    else:
                        print(f"Hint: First {hints} digit(s) of the answer: {qAnswer[:hints]}")
                # wrong was increased when asking the user for input again
                # we decreased the counter since the user asked for a hint (they didn't answer wrong)
                wrong -= 1
            # check if user input was a number
            elif(isinstance(float(answer), float)):
                # make sure user input is in the same format as question answer
                if float(qAnswer) % 1 != 0:
                    answer = f"{float(answer):.2f}"
        # raise an error if user input was neither "y" (after first wrong) or a number
            else:
                raise ValueError("Invalid input. Please input with the correct format.")
        except ValueError:
            print("Invalid input. Please input with the correct format.")
        else:
            break
        
    return answer, hints, wrong

# user can either go up two or one difficulty, stay at their level,
# or go down a level depending on how they do
def next_difficulty(difficulty, time, hints, wrong):
    # easy
    if difficulty <= 5:
        if (hints <= 0 and wrong <= 0 and time < 3*difficulty):
            return difficulty + 2
        if (hints <= 0 and wrong <= 1 and time < 5*difficulty):
            return difficulty + 1
        # we need to make sure difficulty doesn't go below 1
        elif difficulty == 1 or (hints <= 2 and wrong <= 3 and time < 10*difficulty):
            return difficulty
        else:
            return difficulty - 1
    # medium
    elif difficulty <= 10:
        if (hints <= 0 and wrong <= 1 and time < 5*difficulty):
            return difficulty + 2
        if (hints <= 1 and wrong <= 2 and time < 10*difficulty):
            return difficulty + 1
        elif (hints <= 3 and wrong <= 4 and time < 15*difficulty):
            return difficulty
        else:
            return difficulty - 1
    # hard
    else:
        if (hints <= 1 and wrong <= 2 and time < 8*difficulty):
            # we need to make sure difficulty doesn't go over 15
            if difficulty + 2 >= 15:
                return 15
            return difficulty + 2
        if (hints <= 3 and wrong <= 4 and time < 12*difficulty):
            if difficulty + 1 >= 15:
                return 15
            return difficulty + 1
        elif (hints <= 4 and wrong <= 5 and time < 17*difficulty):
            return difficulty
        else:
            return difficulty - 1

# def quiz():
    # put quiz code here

# Start of quiz
print("Welcome to our adaptive math quiz!")
print("Please answer the following questions:\
      \n(for division round to nearest 2 decimals, e.g: 1.345 = 1.35, 1.335 = 1.34)")

totalHints = totalWrong = totalTime = totalQuestions = 0
easy = medium = hard = hardest = 0
difficulty = highest = 1

# loop to decide how many questions the quiz will be
while totalQuestions < 5:
    hints = wrong = 0
    equation, qAnswer = generate_question(difficulty)

    print(f"{equation} = ? | Difficulty:{difficulty}/15")

    # check if the answer is a decimal or not
    if float(qAnswer) % 1 != 0:
        qAnswer = f"{qAnswer:.2f}"
    else:
        qAnswer = f"{qAnswer:.0f}"

    # start timer when we ask input from user
    startTime = time.perf_counter()    
    answer, hints, wrong = get_answer(qAnswer, hints, wrong)

    while answer != qAnswer:
        wrong += 1
        if answer != "y":
            print("Wrong... Type \"y\" if you want a hint")
        answer, hints, wrong = get_answer(qAnswer, hints, wrong)
    # stop timer when the user answers correctly
    endTime = time.perf_counter()
    elapsedTime = endTime - startTime

    # increase counters
    totalHints += hints
    totalWrong += wrong
    totalTime += elapsedTime
    totalQuestions += 1

    # count type of questions answered
    if difficulty > highest:
        highest = difficulty
    if difficulty <= 5:
        easy += 1
    elif difficulty <= 10:
        medium += 1
    else:
        hard += 1
    if difficulty == 15:
        hardest += 1

    print(f"{equation} = {qAnswer}")
    print("Correct!")

    difficulty = next_difficulty(difficulty, elapsedTime, hints, wrong)

print(f"You answered {totalQuestions} questions!\
      \nTotal hints: {totalHints} | Total wrongs: {totalWrong}\
      \nTotal time taken: {totalTime:.2f} seconds | Highest difficulty reached: {highest}/15\
      \nEasy questions: {easy} | Medium questions: {medium} | Hard questions: {hard}\
      \nQuestions answered at highest difficulty: {hardest}")

# Missing features:
# Hints: doesn't take into account if the answer is negative and is a decimal
#        if the answer has a decimal part but doesn't start with 0, it will treat it as a normal number
# Difficulty picker: not optimised, simply done by guessing
# Additional feature:
# Be transparent with user if they will move in difficulty (show timer and stuff)
