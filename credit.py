from enum import Enum

class CardType(Enum):
    AMEX = 1
    MASTERCARD = 2
    VISA = 3
    INVALID = 4

def get_card_number():
    while (True):
        try:
            n = int(input("Number: "))
            return n
        except:
            continue

def main():
    n_str = str(get_card_number())
    type = CardType.INVALID
    if len(n_str) == 15 and n_str[:2] in ["34", "37"]:
        type = CardType.AMEX
    elif len(n_str) == 16 and n_str[:2] in ["51", "52", "53", "54", "55"]:
        type = CardType.MASTERCARD
    elif len(n_str) in [13, 16] and n_str[0] == "4":
        type = CardType.VISA
    # Use Luhn's algorithm.
    products = [2*int(i) for i in n_str[-2::-2]]
    total = sum([p if p < 10 else 1 + p%10 for p in products])
    total += sum([int(i) for i in n_str[-1::-2]])
    if total%10 != 0:
        type = CardType.INVALID
    print(type.name)

main()
