import ExpressionValidation.Validate;

public class Main {
    public static void main(String[] args) {
        if (Validate.isValid(args))
            System.out.println("Da");
        else System.out.println("Nu");
    }
}


