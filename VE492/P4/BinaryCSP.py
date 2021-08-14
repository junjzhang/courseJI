# Hint: from collections import deque
from Interface import *

# = = = = = = = QUESTION 1  = = = = = = = #


def consistent(assignment, csp, var, value):
    """
    Checks if a value assigned to a variable is consistent with all binary constraints in a problem.
    Do not assign value to var.
    Only check if this value would be consistent or not.
    If the other variable for a constraint is not assigned,
    then the new value is consistent with the constraint.

    Args:
        assignment (Assignment): the partial assignment
        csp (ConstraintSatisfactionProblem): the problem definition
        var (string): the variable that would be assigned
        value (value): the value that would be assigned to the variable
    Returns:
        boolean
        True if the value would be consistent with all currently assigned values, False otherwise
    """
    for constraint in (c for c in csp.binaryConstraints if c.affects(var)):
        var2 = constraint.otherVariable(var)
        if assignment.isAssigned(var2):
            if not constraint.isSatisfied(value,
                                          assignment.assignedValues[var2]):
                return False
    return True


def recursiveBacktracking(assignment, csp, orderValuesMethod,
                          selectVariableMethod, inferenceMethod):
    """
    Recursive backtracking algorithm.
    A new assignment should not be created.
    The assignment passed in should have its domains updated with inferences.
    In the case that a recursive call returns failure or a variable assignment is incorrect,
    the inferences made along the way should be reversed.
    See maintainArcConsistency and forwardChecking for the format of inferences.

    Examples of the functions to be passed in:
    orderValuesMethod: orderValues, leastConstrainingValuesHeuristic
    selectVariableMethod: chooseFirstVariable, minimumRemainingValuesHeuristic
    inferenceMethod: noInferences, maintainArcConsistency, forwardChecking

    Args:
        assignment (Assignment): a partial assignment to expand upon
        csp (ConstraintSatisfactionProblem): the problem definition
        orderValuesMethod (function<assignment, csp, variable> returns list<value>):
            a function to decide the next value to try
        selectVariableMethod (function<assignment, csp> returns variable):
            a function to decide which variable to assign next
        inferenceMethod (function<assignment, csp, variable, value> returns set<variable, value>):
            a function to specify what type of inferences to use
    Returns:
        Assignment
        A completed and consistent assignment. None if no solution exists.
    """
    if assignment.isComplete():
        return assignment

    var = selectVariableMethod(assignment, csp)
    for value in orderValuesMethod(assignment, csp, var):
        if consistent(assignment, csp, var, value):
            assignment.assignedValues[var] = value
            inferences = inferenceMethod(assignment, csp, var, value)
            if inferences is not None:
                result = recursiveBacktracking(assignment, csp,
                                               orderValuesMethod,
                                               selectVariableMethod,
                                               inferenceMethod)
                if result is not None:
                    return result
                for inference in inferences:
                    assignment.varDomains[inference[0]].add(inference[1])
            assignment.assignedValues[var] = None

    return None


def eliminateUnaryConstraints(assignment, csp):
    """
    Uses unary constraints to eleminate values from an assignment.

    Args:
        assignment (Assignment): a partial assignment to expand upon
        csp (ConstraintSatisfactionProblem): the problem definition
    Returns:
        Assignment
        An assignment with domains restricted by unary constraints. None if no solution exists.
    """
    domains = assignment.varDomains
    for var in domains:
        for constraint in (c for c in csp.unaryConstraints if c.affects(var)):
            for value in (v for v in list(domains[var])
                          if not constraint.isSatisfied(v)):
                domains[var].remove(value)
                # Failure due to invalid assignment
                if len(domains[var]) == 0:
                    return None
    return assignment


def chooseFirstVariable(assignment, csp):
    """
    Trivial method for choosing the next variable to assign.
    Uses no heuristics.
    """
    for var in csp.varDomains:
        if not assignment.isAssigned(var):
            return var


# = = = = = = = QUESTION 2  = = = = = = = #


def minimumRemainingValuesHeuristic(assignment, csp):
    """
    Selects the next variable to try to give a value to in an assignment.
    Uses minimum remaining values heuristic to pick a variable. Use degree heuristic for breaking ties.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
    Returns:
        the next variable to assign
    """
    nextVar = None
    domains = assignment.varDomains

    unassigned = [(len(domains[var]), var) for var in domains.keys()
                  if domains[var] and not assignment.isAssigned(var)]
    unassigned.sort()
    ties = [
        varInfo[1] for varInfo in unassigned if varInfo[0] == unassigned[0][0]
    ]

    if len(ties) == 1:
        return ties[0]

    maxDegree = float("-inf")
    for var in ties:
        degree = 0
        for constraint in (c for c in csp.binaryConstraints if c.affects(var)):
            if not assignment.isAssigned(constraint.otherVariable(var)):
                degree += 1
        if degree > maxDegree:
            maxDegree = degree
            nextVar = var
    return nextVar


def orderValues(assignment, csp, var):
    """
    Trivial method for ordering values to assign.
    Uses no heuristics.
    """
    return list(assignment.varDomains[var])


# = = = = = = = QUESTION 3  = = = = = = = #


def leastConstrainingValuesHeuristic(assignment, csp, var):
    """
    Creates an ordered list of the remaining values left for a given variable.
    Values should be attempted in the order returned.
    The least constraining value should be at the front of the list.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var (string): the variable to be assigned the values
    Returns:
        list<values>
        a list of the possible values ordered by the least constraining value heuristic
    """
    values = list(assignment.varDomains[var])
    values.sort(key=lambda x: len(
        list(filter(lambda c: c.affects(var), csp.binaryConstraints))))
    return values


def noInferences(assignment, csp, var, value):
    """
    Trivial method for making no inferences.
    """
    return set([])


# = = = = = = = QUESTION 4  = = = = = = = #


def forwardChecking(assignment, csp, var, value):
    """
    Implements the forward checking algorithm.
    Each inference should take the form of (variable, value)
    where the value is being removed from the domain of variable.
    This format is important so that the inferences can be reversed
    if they result in a conflicting partial assignment.
    If the algorithm reveals an inconsistency,
    any inferences made should be reversed before ending the function.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var (string): the variable that has just been assigned a value
        value (string): the value that has just been assigned
    Returns:
        set< tuple<variable, value> >
        the inferences made in this call or None if inconsistent assignment
    """
    inferences = set([])
    domains = assignment.varDomains

    if not consistent(assignment, csp, var, value):
        return None

    for constraint in (c for c in csp.binaryConstraints if c.affects(var)):
        neighbor = constraint.otherVariable(var)
        neighborValues = list(domains[neighbor])
        for neighborValue in neighborValues:
            if not constraint.isSatisfied(value, neighborValue):
                inferences.add((neighbor, neighborValue))
                domains[neighbor].remove(neighborValue)
            if not domains[neighbor]:
                for inference in inferences:
                    domains[inference[0]].add(inference[1])
                return None

    return inferences


# = = = = = = = QUESTION 5  = = = = = = = #


def revise(assignment, csp, var1, var2, constraint):
    """
    Helper function to maintainArcConsistency and AC3.
    Remove values from var2 domain if constraint cannot be satisfied.
    Each inference should take the form of (variable, value)
    where the value is being removed from the domain of variable.
    This format is important so that the inferences can be reversed
    if they result in a conflicting partial assignment.
    If the algorithm reveals an inconsistency,
    any inferences made should be reversed before ending the function.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var1 (string): the variable with consistent values
        var2 (string): the variable that should have inconsistent values removed
        constraint (BinaryConstraint): the constraint connecting var1 and var2
    Returns:
        set<tuple<variable, value>>
        the inferences made in this call or None if inconsistent assignment
    """
    inferences = set([])
    domains = assignment.varDomains

    for value2 in domains[var2]:
        flag = False
        for value1 in domains[var1]:
            if constraint.isSatisfied(value1, value2):
                flag = True
                break
        if not flag:
            inferences.add((var2, value2))

    if len(inferences) == len(assignment.varDomains[var2]):
        return None
    for inference in inferences:
        domains[inference[0]].remove(inference[1])

    return inferences


def maintainArcConsistency(assignment, csp, var, value):
    """
    Implements the maintaining arc consistency algorithm.
    Inferences take the form of (variable, value)
    where the value is being removed from the domain of variable.
    This format is important so that the inferences can be reversed
    if they result in a conflicting partial assignment.
    If the algorithm reveals an inconsistency,
    and inferences made should be reversed before ending the function.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
        var (string): the variable that has just been assigned a value
        value (string): the value that has just been assigned
    Returns:
        set<<variable, value>>
        the inferences made in this call or None if inconsistent assignment
    """
    inferences = set([])
    domains = assignment.varDomains

    constraints = (constraint for constraint in csp.binaryConstraints
                   if constraint.affects(var))
    queue = [(var, constraint.otherVariable(var), constraint)
             for constraint in constraints
             if not assignment.isAssigned(constraint.otherVariable(var))]

    while queue:
        var1, var2, constraint = queue.pop()
        revisedInference = revise(assignment, csp, var1, var2, constraint)
        if revisedInference is None:
            for inference in inferences:
                domains[inference[0]].add(inference[1])
            return None
        if revisedInference:
            inferences = inferences.union(revisedInference)
            for constraint in (c for c in csp.binaryConstraints
                               if c.affects(var2)):
                var3 = constraint.otherVariable(var2)
                if not assignment.isAssigned(var3):
                    queue.append((var2, var3, constraint))

    return inferences


# = = = = = = = QUESTION 6  = = = = = = = #


def AC3(assignment, csp):
    """
    AC3 algorithm for constraint propagation.
    Used as a pre-processing step to reduce the problem
    before running recursive backtracking.

    Args:
        assignment (Assignment): the partial assignment to expand
        csp (ConstraintSatisfactionProblem): the problem description
    Returns:
        Assignment
        the updated assignment after inferences are made or None if an inconsistent assignment
    """
    inferences = set([])

    domains = assignment.varDomains

    fGen1 = lambda x: (x.var1, x.var2, x)
    fGen2 = lambda x: (x.var2, x.var1, x)
    queue = [
        fGen(constraint) for constraint in csp.binaryConstraints
        for fGen in (fGen1, fGen2)
    ]

    while queue:
        var1, var2, constraint = queue.pop()
        revisedInference = revise(assignment, csp, var1, var2, constraint)
        if revisedInference is None:
            for inference in inferences:
                domains[inference[0]].add(inference[1])
            return None

        if revisedInference:
            inferences.union(revisedInference)
            for constraint in (c for c in csp.binaryConstraints
                               if c.affects(var2)):
                var3 = constraint.otherVariable(var2)
                queue.append((var2, var3, constraint))

    return assignment


def solve(csp,
          orderValuesMethod=leastConstrainingValuesHeuristic,
          selectVariableMethod=minimumRemainingValuesHeuristic,
          inferenceMethod=forwardChecking,
          useAC3=True):
    """
    Solves a binary constraint satisfaction problem.

    Args:
        csp (ConstraintSatisfactionProblem): a CSP to be solved
        orderValuesMethod (function): a function to decide the next value to try
        selectVariableMethod (function): a function to decide which variable to assign next
        inferenceMethod (function): a function to specify what type of inferences to use
        useAC3 (boolean): specifies whether to use the AC3 pre-processing step or not
    Returns:
        dictionary<string, value>
        A map from variables to their assigned values. None if no solution exists.
    """
    assignment = Assignment(csp)

    assignment = eliminateUnaryConstraints(assignment, csp)
    if assignment is None:
        return assignment

    if useAC3:
        assignment = AC3(assignment, csp)
        if assignment is None:
            return assignment

    assignment = recursiveBacktracking(assignment, csp, orderValuesMethod,
                                       selectVariableMethod, inferenceMethod)
    if assignment is None:
        return assignment

    return assignment.extractSolution()
