from itertools import product

# We are only interested in TMs with a single transition to the halt state
choices = ["00", "01", "02", "03", "04", "05",
           "10", "11", "12", "13", "14", "15"]

halt_state = "21"


def generate_tms(filepath, test_function):
    lines = []
    for choice in product(choices, repeat=5):
        choice = list(choice)
        possible_choices = ["".join(choice[:i] + [halt_state] + choice[i:])
                            for i in range(6)]

        lines += [x for x in possible_choices if test_function(x)]

    lines = sorted(lines)

    with open(filepath, "w+") as f:
        f.write("\n".join(lines))
