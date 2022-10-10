package ExpressionLogic;

import ExpressionLogic.ComplexExpressionOperations.AdditionExpression;
import ExpressionLogic.ComplexExpressionOperations.DivisionExpression;
import ExpressionLogic.ComplexExpressionOperations.MultiplicationExpression;
import ExpressionLogic.ComplexExpressionOperations.SubstractionExpression;

public class ExpressionFactory {
    private static ExpressionFactory instance=new ExpressionFactory();
    private ExpressionFactory(){}
    public static ExpressionFactory getInstance(){
        return instance;
    }
    public ComplexExpression createExpression(Operation operation,NumarComplex[] args){
        switch (operation){
            case ADDITION:
                return new AdditionExpression(operation,args);
            case DIVISION:
                return new DivisionExpression(operation,args);
            case SUBSTRACTION:
                return new SubstractionExpression(operation,args);
            case MULTIPLICATION:
                return new MultiplicationExpression(operation,args);
        }
        return null;
    }
}
