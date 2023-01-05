package ExpressionLogic.ComplexExpressionOperations;

import ExpressionLogic.ComplexExpression;
import ExpressionLogic.NumarComplex;
import ExpressionLogic.Operation;

public class DivisionExpression extends ComplexExpression {
    public DivisionExpression(Operation operation, NumarComplex[] args) {
        super(operation, args);
    }
    @Override
    public NumarComplex executeOneOperation(NumarComplex n1, NumarComplex n2){
        return NumarComplex.impartire(n1, n2);
    }
}
