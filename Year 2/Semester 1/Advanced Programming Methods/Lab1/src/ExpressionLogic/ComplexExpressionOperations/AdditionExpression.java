package ExpressionLogic.ComplexExpressionOperations;

import ExpressionLogic.ComplexExpression;
import ExpressionLogic.NumarComplex;
import ExpressionLogic.Operation;

public class AdditionExpression extends ComplexExpression {
    public AdditionExpression(Operation operation, NumarComplex[] args) {
        super(operation, args);
    }
    @Override
    public NumarComplex executeOneOperation(NumarComplex n1, NumarComplex n2){
        return NumarComplex.adunare(n1, n2);
    }
}
