
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            // Initialize vending machine items (true = available, false = empty)
            boolean[][] items = {
                {true, true, true}, // Row A
                {true, true, true}, // Row B
                {true, true, true} // Row C
            };

            while (true) {
                // Check if all items are gone
                if (allEmpty(items)) {
                    clearScreen();
                    displayVendingMachine(items);
                    System.out.println("nothing is here, sorry!");
                    break;
                }

                // Clear screen and display the vending machine
                clearScreen();
                displayVendingMachine(items);

                // Get user input
                System.out.print("Enter item to pick: ");
                String input = scanner.nextLine().trim().toUpperCase();

                // Parse input (e.g., "A1")
                if (input.length() != 2) {
                    System.out.println("Invalid input! Please use format like A1, B2, etc.");
                    System.out.print("Press Enter to continue...");
                    scanner.nextLine();
                    continue;
                }

                char row = input.charAt(0);
                char col = input.charAt(1);

                // Validate row (A, B, C)
                if (row < 'A' || row > 'C') {
                    System.out.println("Invalid row! Please use A, B, or C.");
                    System.out.print("Press Enter to continue...");
                    scanner.nextLine();
                    continue;
                }

                // Validate column (1, 2, 3)
                if (col < '1' || col > '3') {
                    System.out.println("Invalid column! Please use 1, 2, or 3.");
                    System.out.print("Press Enter to continue...");
                    scanner.nextLine();
                    continue;
                }

                int rowIndex = row - 'A';
                int colIndex = col - '1';

                // Check if item is available
                if (items[rowIndex][colIndex]) {
                    items[rowIndex][colIndex] = false;
                    System.out.println("there you go!");
                    System.out.print("Press Enter to continue...");
                    scanner.nextLine();
                } else {
                    System.out.println("item not available");
                    System.out.print("Press Enter to continue...");
                    scanner.nextLine();
                }
            }
        }
    }

    // Display the vending machine
    private static void displayVendingMachine(boolean[][] items) {
        char[] rows = {'A', 'B', 'C'};

        for (int i = 0; i < 3; i++) {
            // Top border
            System.out.println("+-+ +-+ +-+");

            // Item row
            for (int j = 0; j < 3; j++) {
                if (items[i][j]) {
                    System.out.print("+" + rows[i] + "+ ");
                } else {
                    System.out.print("+.+ ");
                }
            }
            System.out.println();

            // Bottom border
            System.out.println("+-+ +-+ +-+");
        }
    }

    // Check if all items are empty
    private static boolean allEmpty(boolean[][] items) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (items[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // Clear the screen using ANSI escape codes
    private static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}
