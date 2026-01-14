/**
 * @file ascii.c
 * @brief ASCII art strings implementation.
 */

const char* hangman_string(int misses)
{
    switch(misses)
    {
    case 0:
        return "        \n"
               "        \n"
               "        \n"
               "        \n"
               "        \n"
               "        \n"
               "        \n"
               " ------ \n";
    case 1:
        return "        \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 2:
        return "------  \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 3:
        return "------  \n"
               " |    | \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 4:
        return "------  \n"
               " |    | \n"
               " |    O \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 5:
        return "------  \n"
               " |    | \n"
               " |    O \n"
               " |    | \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 6:
        return "------  \n"
               " |    | \n"
               " |    O \n"
               " |   /| \n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 7:
        return "------  \n"
               " |    | \n"
               " |    O \n"
               " |   /|\\\n"
               " |      \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 8:
        return "------  \n"
               " |    | \n"
               " |    O \n"
               " |   /|\\\n"
               " |   /  \n"
               " |      \n"
               " |      \n"
               " ------ \n";
    case 9:
        return "------  \n"
               " |    | \n"
               " |    O \n"
               " |   /|\\\n"
               " |   / \\\n"
               " |      \n"
               " |      \n"
               " ------ \n";
    default:
        return "ERROR";
        break;
    }
}
