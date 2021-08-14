import mdp, util

from learningAgents import ValueEstimationAgent
import collections


class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, Mdp, discount=0.9, iterations=100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = Mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter()  # A Counter is a dict with default 0
        self.runValueIteration()

    def runValueIteration(self):
        # Write value iteration code here
        "*** YOUR CODE HERE ***"
        for _ in range(self.iterations):
            newValues = self.values.copy()
            states = self.mdp.getStates()

            for state in states:
                if self.mdp.isTerminal(state):
                    continue

                QValues = [
                    self.getQValue(state, action)
                    for action in self.mdp.getPossibleActions(state)
                ]

                newValues[state] = max(QValues)

            self.values = newValues

    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]

    def computeQValueFromValues(self, state, action):
        """
          Compute the Q-value of action in state from the
          value function stored in self.values.
        """
        "*** YOUR CODE HERE ***"
        valueChances = [
            prob * (self.mdp.getReward(state, action, nextState) +
                    self.discount * self.getValue(nextState))
            for nextState, prob in self.mdp.getTransitionStatesAndProbs(
                state, action)
        ]

        return sum(valueChances)

    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.

          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"
        actions = util.Counter()

        for action in self.mdp.getPossibleActions(state):
            actions[action] = self.getQValue(state, action)

        return actions.argMax()

    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)


class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        An AsynchronousValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs cyclic value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount=0.9, iterations=1000):
        """
          Your cyclic value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy. Each iteration
          updates the value of only one state, which cycles through
          the states list. If the chosen state is terminal, nothing
          happens in that iteration.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state)
              mdp.isTerminal(state)
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        states = self.mdp.getStates()
        statesSize = len(states)

        for i in range(self.iterations):
            state = states[i % statesSize]

            if self.mdp.isTerminal(state):
                continue

            self.values[state] = max([
                self.getQValue(state, action)
                for action in self.mdp.getPossibleActions(state)
            ])


class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A PrioritizedSweepingValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs prioritized sweeping value iteration
        for a given number of iterations using the supplied parameters.
    """
    def __init__(self, mdp, discount=0.9, iterations=100, theta=1e-5):
        """
          Your prioritized sweeping value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        predecessors = {}
        states = self.mdp.getStates()

        for state in states:
            if self.mdp.isTerminal(state):
                continue
            for action in self.mdp.getPossibleActions(state):
                for nextState, _ in self.mdp.getTransitionStatesAndProbs(
                        state, action):
                    if nextState in predecessors:
                        predecessors[nextState].add(state)
                    else:
                        predecessors[nextState] = {state}

        Queue = util.PriorityQueue()

        for state in self.mdp.getStates():
            if self.mdp.isTerminal(state):
                continue
            QValues = [
                self.computeQValueFromValues(state, action)
                for action in self.mdp.getPossibleActions(state)
            ]

            difference = abs(self.values[state] - max(QValues))

            Queue.update(state, -difference)

        for _ in range(self.iterations):
            if Queue.isEmpty():
                break
            state = Queue.pop()
            if not self.mdp.isTerminal(state):
                self.values[state] = max([
                    self.computeQValueFromValues(state, action)
                    for action in self.mdp.getPossibleActions(state)
                ])

            for predecessor in predecessors[state]:
                QValues = [
                    self.computeQValueFromValues(predecessor, action)
                    for action in self.mdp.getPossibleActions(predecessor)
                ]
                difference = abs(self.values[predecessor] - max(QValues))

                if difference > self.theta:
                    Queue.update(predecessor, -difference)
