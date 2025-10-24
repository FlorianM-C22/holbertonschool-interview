#!/usr/bin/python3

def isWinner(x, nums):
    """
    Determine the winner of the prime game.

    Args:
        x: number of rounds
        nums: array of n values for each round

    Returns:
        name of the player that won the most rounds, or None if tied
    """
    if not nums or x <= 0:
        return None

    # Count wins for each player
    maria_wins = 0
    ben_wins = 0

    for n in nums:
        if n <= 0:
            # No primes available, Ben wins by default
            ben_wins += 1
            continue

        # Get all primes up to n
        primes = get_primes(n)

        if not primes:
            # No primes available, Ben wins
            ben_wins += 1
            continue

        # Determine winner based on number of primes
        # If odd number of primes, Maria (first player) wins
        # If even number of primes, Ben (second player) wins
        if len(primes) % 2 == 1:
            maria_wins += 1
        else:
            ben_wins += 1

    # Determine overall winner
    if maria_wins > ben_wins:
        return "Maria"
    elif ben_wins > maria_wins:
        return "Ben"
    else:
        return None


def get_primes(n):
    """
    Get all prime numbers up to and including n.

    Args:
        n: upper bound (inclusive)

    Returns:
        list of prime numbers
    """
    if n < 2:
        return []

    # Sieve of Eratosthenes
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, int(n ** 0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False

    return [i for i in range(2, n + 1) if is_prime[i]]
