#!/usr/bin/python3

def makeChange(coins, total):
    """
    Determine the fewest number of coins needed to make change 
    for a given amount.

    Args:
        coins (list): List of coin values in descending order.
        total (int): The amount of money to make change for.

    Returns:
        int: The fewest number of coins needed to make change 
        for the total amount.
    """
    if total <= 0:
        return 0

    # Initialize a list to store the minimum number of coins for each amount
    dp = [float('inf')] * (total + 1)

    # Base case: 0 coins needed for 0 total
    dp[0] = 0

    # Fill the dp array
    for amount in range(1, total + 1):
        for coin in coins:
            if coin <= amount:
                dp[amount] = min(dp[amount], dp[amount - coin] + 1)

    # Return -1 if total cannot be met, otherwise return the result
    return dp[total] if dp[total] != float('inf') else -1
