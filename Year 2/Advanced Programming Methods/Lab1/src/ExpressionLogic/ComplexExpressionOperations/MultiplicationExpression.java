package ExpressionLogic.ComplexExpressionOperations;

import ExpressionLogic.ComplexExpression;
import ExpressionLogic.NumarComplex;
import ExpressionLogic.Operation;

public class MultiplicationExpression extends ComplexExpression {
    public MultiplicationExpression(Operation operation, NumarComplex[] args) {
        super(operation, args);
    }
    @Override
    public NumarComplex executeOneOperation(NumarComplex n1, NumarComplex n2){
        return NumarComplex.inmultire(n1, n2);
    }
}
