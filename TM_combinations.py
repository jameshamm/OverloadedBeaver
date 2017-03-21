from itertools import product

# We are only interested in TMs with a single transition to the halt state
choices = ["00", "01", "02", "03", "04", "05",
           "10", "11", "12", "13", "14", "15"]

halt_state = "21"


def test_nb(x):
    """Take a string, tell some of them they are stupid

    Return True if on non blank input, the TM will loop or never halt"""
    if any(x.startswith(y) for y in ("0000", "0004", "0400", "0404")):
        return False
    # The TM can't leave a state once it gets to it.
    # Either it doesn't use that state, or it loops
    # Neither is TM we are interested in
    if "0" == x[0] == x[2] == x[4] or "1" == x[6] == x[8] == x[10]:
        return False
    return True


def test_b(x):
    """Take a string, tell some of them they are idiots

    Return True if on blank input the TM will
    loop, never halt or stop immediately"""
    # We known what the first cell reads, so we can reason about
    # the first couple of steps
    if x[4] == "2":
        # halts immediately
        return False
    if x[4:6] in ("02", "05"):
        # only writes blank to the tape
        return False
    if x[5] == "0":
        # writes a 0, moves left so stays on
        if x[4] == "0" and x[0:2] == "00":
            # same state, writes 0 and moves left
            return False
        if x[4] == "1" and x[6:8] == "10":
            # other state, writes 0 and moves left
            return False
    elif x[5] == "1":
        if x[4] == "0" and x[2:4] == "01":
            return False
        if x[4] == "1" and x[8:10] == "11":
            return False

    if "0" == x[0] == x[2] == x[4] or "1" == x[6] == x[8] == x[10]:
        return False
    return True


def generate_TMs(filepath, test_function):
    lines = []
    for choice in product(choices, repeat=5):
        choice = list(choice)
        possible_choices = ["".join(choice[:i] + [halt_state] + choice[i:])
                            for i in range(6)]

        lines += [x for x in possible_choices if test_function(x)]

    lines = sorted(lines)

    with open(filepath, "w+") as f:
        f.write("\n".join(lines))

if __name__ == "__main__":
    print("Generating nb TMs")
    generate_TMs("data/nb_TMs.txt", test_nb)

    print("Generating b TMs")
    generate_TMs("data/b_TMs.txt", test_b)

    print("DONE")
