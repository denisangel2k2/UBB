package Tests;

import ExpressionLogic.ComplexExpression;
import ExpressionLogic.ExpressionFactory;
import ExpressionLogic.NumarComplex;
import ExpressionLogic.Operation;

public class Tests {
    public static void run(){
        NumarComplex[] args =new NumarComplex[3];
        args[0]=new NumarComplex(1,1);
        args[1]=new NumarComplex(1,1);
        args[2]=new NumarComplex(1,2);
        ExpressionFactory factory=ExpressionFactory.getInstance();
        ComplexExpression expression=factory.createExpression(Operation.ADDITION,args);
        System.out.println(expression.execute().toString());
    }


}
