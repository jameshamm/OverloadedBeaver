def is_interesting(x):
    """
    Some hand made patterns for TMs that will loop forever on blank input
    """
    # Never overwrites a symbol
    if x[0] == '1' and x[1] == '0' and x[2] == '1' and x[3] == '4' and x[6] == '1' and x[7] == '0' and x[8] == '1' and x[9] == '4':
        return False

    # Sets everything to 0, loops on 0
    if x[0] == '1' and x[1] == '0' and x[2] == '1' and x[3] == '0' and x[6] == '1' and x[7] == '0':
        return False
    # Dual of above
    if x[0] == '1' and x[1] == '4' and x[2] == '1' and x[3] == '4' and x[8] == '1' and x[9] == '4':
        return False

    # Loops between states doing nothing
    if x[0] == '1' and x[1] == '0' and x[2] == '1' and x[3] == '4' and x[6] == '0' and x[7] == '0' and x[8] == '0' and x[9] == '4':
        return False
    # Almost dual of above
    if x[0] == '1' and x[1] == '4' and x[2] == '1' and x[3] == '0' and x[6] == '0' and x[7] == '4' and x[8] == '0' and x[9] == '0':
        return False

    # Too many blanks, always goes right with blanks
    if x[0] == '0' and x[1] in ('1', '3', '5') and x[2] == '0' and x[3] in ('1', '3', '5') and x[4] == '1' and x[5] in ('1', '3', '5') and x[10] in ('0', '1') and x[11] in ('1', '3', '5'):
        return False

    # Loop on 0, or 0 -> 1, until end of input, then go forever
    if x[0] == '0' and x[1] in ('0', '4') and x[2] == '0' and x[3] == '1' and x[4] == '1' and x[5] in ('1', '3', '5') and x[10] in ('0', '1') and x[11] in ('1', '3', '5'):
        return False

    return True


def remove_bad(input_file, output_file):
    with open(input_file, "r") as f:
        lines = f.readlines()
    
    lines = [line.strip() for line in lines]
    seen = set()

    lines = [line for line in lines if is_interesting(line)]

    lines = sorted(lines)

    with open(output_file, "w+") as f:
        f.write("\n".join(lines))


if __name__ == "__main__":
    print("Finding some bad (bn) TMs")
    input_file, output_file = "../data/dualless_nb_TMs.txt", "../data/trimmed_nb_TMs.txt"
    remove_bad(input_file, output_file)
    print("DONE")