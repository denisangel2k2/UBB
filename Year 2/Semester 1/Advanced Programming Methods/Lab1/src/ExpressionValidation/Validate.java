package ExpressionValidation;

public class Validate {
    private static boolean isValidNumber(String stringNumber) {
        int numberOfI = 0;
        int numberOfSigns = 0;
        boolean areLetters = false;
        char[] numberArray = stringNumber.toCharArray();
        for (int i = 0; i < numberArray.length && !areLetters; i++) {
            if (numberArray[i] == 'i')
                numberOfI++;
            else if (numberArray[i] == '+' || numberArray[i] == '-' || numberArray[i] == '/' || numberArray[i] == '*')
                numberOfSigns++;
            else if (numberArray[i] >= 'a' && numberArray[i] <= 'z' || numberArray[i] >= 'A' && numberArray[i] <= 'Z')
                areLetters = true;
        }
        if (areLetters)
            return false;
        if (numberOfI == 1 && numberOfSigns == 2)
            return true;
        else return false;
    }

    public static boolean isValid(String[] expression) {
        /*
        Function that checks whether the given expression as a parameter is valid or not
        */
        boolean state = true;
        int numberOfSigns = 0;
        int numberOfNumbers = 0;
        //checking the signs
        for (int i = 1; i < expression.length && state; i += 2) {
            numberOfSigns++;
            if (!expression[i].matches("[+\\-*/]"))
                state = false;
        }
        //checking the numbers

        for (int i = 0; i < expression.length && state; i += 2) {
            numberOfNumbers++;
            if (!isValidNumber(expression[i]))
                state = false;
        }
        if (state)
            if (!(numberOfSigns == numberOfNumbers - 1))
                state = false;
        return state;
    }

}
