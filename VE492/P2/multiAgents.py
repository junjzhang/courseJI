from util import manhattanDistance
from game import Directions
import random, util

from game import Agent


class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """
    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [
            self.evaluationFunction(gameState, action) for action in legalMoves
        ]
        bestScore = max(scores)
        bestIndices = [
            index for index in range(len(scores)) if scores[index] == bestScore
        ]
        chosenIndex = random.choice(
            bestIndices)  # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [
            ghostState.scaredTimer for ghostState in newGhostStates
        ]

        "*** YOUR CODE HERE ***"
        newFoodList = newFood.asList()
        currentFoodList = currentGameState.getFood().asList()
        newGhost = [(state.getPosition()[0], state.getPosition()[1])
                    for state in newGhostStates]

        if (min(newScaredTimes) <= 0) and (newPos in newGhost):
            return float("-inf")
        elif newPos in currentFoodList:
            return float("inf")
        else:
            closestFood = sorted(
                newFoodList,
                key=lambda foodPos: manhattanDistance(foodPos, newPos))
            closestGhost = sorted(
                newGhost,
                key=lambda ghostPos: manhattanDistance(ghostPos, newPos))

        return 1 / manhattanDistance(closestFood[0],
                                     newPos) - 1 / manhattanDistance(
                                         closestGhost[0], newPos)


def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()


class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """
    def __init__(self, evalFn='scoreEvaluationFunction', depth='2'):
        self.index = 0  # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

    def isTerminal(self, state, currentDepth):
        return state.isWin() or state.isLose() or currentDepth == self.depth


class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """
    def minValue(self, state, currentDepth, index):
        if self.isTerminal(state, currentDepth):
            return self.evaluationFunction(state)
        else:
            value = float('inf')
            actions = state.getLegalActions(index)
            for action in actions:
                nextState = state.generateSuccessor(index, action)
                if index == self.numGhost:
                    value = min(value,
                                self.maxValue(nextState, currentDepth + 1))
                else:
                    value = min(
                        value, self.minValue(nextState, currentDepth,
                                             index + 1))
            return value

    def maxValue(self, state, currentDepth):
        if self.isTerminal(state, currentDepth):
            return self.evaluationFunction(state)
        else:
            value = float('-inf')
            for action in state.getLegalActions(0):
                nextState = state.generateSuccessor(0, action)
                value = max(value, self.minValue(nextState, currentDepth, 1))
            return value

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        # begin with pacman
        pacManActions = gameState.getLegalActions(0)
        self.numGhost = gameState.getNumAgents() - 1
        values = [
            self.minValue(gameState.generateSuccessor(0, action), 0, 1)
            for action in pacManActions
        ]
        maxIdx = max(range(len(values)), key=values.__getitem__)
        return pacManActions[maxIdx]


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """
    def minValue(self, state, currentDepth, index, alpha, beta):
        if self.isTerminal(state, currentDepth):
            return self.evaluationFunction(state)
        else:
            value = float('inf')
            actions = state.getLegalActions(index)
            for action in actions:
                nextState = state.generateSuccessor(index, action)
                if index == self.numGhost:
                    value = min(
                        value,
                        self.maxValue(nextState, currentDepth + 1, alpha,
                                      beta))
                else:
                    value = min(
                        value,
                        self.minValue(nextState, currentDepth, index + 1,
                                      alpha, beta))

                if value < alpha:
                    return value
                beta = min(beta, value)

            return value

    def maxValue(self, state, currentDepth, alpha, beta):
        if self.isTerminal(state, currentDepth):
            return self.evaluationFunction(state)
        else:
            value = float('-inf')
            actions = state.getLegalActions(0)
            for action in actions:
                nextState = state.generateSuccessor(0, action)
                value = max(
                    value,
                    self.minValue(nextState, currentDepth, 1, alpha, beta))
                if value > beta:
                    return value

                alpha = max(alpha, value)

            return value

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"

        alpha = float('-inf')
        beta = float('inf')
        self.numGhost = gameState.getNumAgents() - 1

        maxValue = float('-inf')
        pacManActions = gameState.getLegalActions(0)
        maxIdx = 0
        for idx, action in enumerate(pacManActions):
            nextState = gameState.generateSuccessor(0, action)
            value = self.minValue(nextState, 0, 1, alpha, beta)

            if value > maxValue:
                maxValue = value
                maxIdx = idx

            alpha = max(alpha, value)

        return pacManActions[maxIdx]


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """
    def expectedValue(self, state, depth, index):
        if self.isTerminal(state, depth):
            return self.evaluationFunction(state)
        else:
            value = 0
            actions = state.getLegalActions(index)
            for action in actions:
                nextState = state.generateSuccessor(index, action)
                if index == self.numGhost:
                    value += self.maxValue(nextState, depth + 1)
                else:
                    value += self.expectedValue(nextState, depth, index + 1)

            return value / len(actions)

    def maxValue(self, state, currentDepth):
        if self.isTerminal(state, currentDepth):
            return self.evaluationFunction(state)
        else:
            actions = state.getLegalActions(0)
            value = float('-inf')
            for action in actions:
                nextState = state.generateSuccessor(0, action)
                value = max(value,
                            self.expectedValue(nextState, currentDepth, 1))

            return value

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        pacManActions = gameState.getLegalActions(0)
        self.numGhost = gameState.getNumAgents() - 1
        values = [
            self.expectedValue(gameState.generateSuccessor(0, action), 0, 1)
            for action in pacManActions
        ]
        maxIdx = max(range(len(values)), key=values.__getitem__)
        return pacManActions[maxIdx]


def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    newPos = currentGameState.getPacmanPosition()
    newFood = currentGameState.getFood()
    newGhostStates = currentGameState.getGhostStates()

    disCapsule = [
        manhattanDistance(newPos, x) for x in currentGameState.getCapsules()
    ] if currentGameState.getCapsules() else []
    disFood = [manhattanDistance(newPos, x) for x in newFood.asList()]

    value = currentGameState.getScore()

    if disFood:
        value += 10 / min(disFood)
    for ghost in newGhostStates:
        disGhost = manhattanDistance(newPos, ghost.getPosition())
        if disGhost:
            if ghost.scaredTimer > 0:
                value += 50 / disGhost
            else:
                if disCapsule:
                    value += 2 / min(disCapsule)
                value -= 10 / disGhost**1.5
        else:
            value = float("-inf")

    return value


# Abbreviation
better = betterEvaluationFunction
