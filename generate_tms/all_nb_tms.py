from gen_tms import generate_tms


def is_interesting(x):
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


if __name__ == "__main__":
    print("Generating non-blank input TMs")
    generate_tms("../data/all_nb_TMs.txt", is_interesting)
    print("DONE")
