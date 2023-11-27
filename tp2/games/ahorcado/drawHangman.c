void drawHangman(int step)
{

    switch (step)
    {
    case 6:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("            |\n");
        printf("            |\n");
        printf("            |\n");
        printf("            |\n");
        printf("       =========\n");
        break;

    case 5:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("        O   |\n");
        printf("            |\n");
        printf("            |\n");
        printf("            |\n");
        printf("       =========\n");
        break;

    case 4:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("        O   |\n");
        printf("       /    |\n");
        printf("            |\n");
        printf("            |\n");
        printf("       =========\n");
        break;

    case 3:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("        O   |\n");
        printf("       / \\  |\n");
        printf("            |\n");
        printf("            |\n");
        printf("       =========\n");
        break;

    case 2:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("        O   |\n");
        printf("       /|\\  |\n");
        printf("            |\n");
        printf("            |\n");
        printf("       =========\n");
        break;

    case 1:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("        O   |\n");
        printf("       /|\\  |\n");
        printf("       /    |\n");
        printf("            |\n");
        printf("       =========\n");
        break;

    case 0:
        printf("        +---+\n");
        printf("        |   |\n");
        printf("        O   |\n");
        printf("       /|\\  |\n");
        printf("       / \\  |\n");
        printf("            |\n");
        printf("       =========\n");
        break;
    default:
        break;
    }
}