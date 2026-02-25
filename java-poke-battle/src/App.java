
public class App {

    public static void main(String[] args) throws Exception {
        clearScreen();
        System.out.println("Welcome to Poke Battle!");
        System.out.println("1. Start Battle");
        System.out.println("0. Exit");
        int choice = System.in.read() - '0';

        switch (choice) {
            case 1 -> Game.gameStart();
            case 0 -> {
                System.out.println("Exiting...");
                System.exit(0);
            }
            default ->
                System.out.println("Invalid choice. Please try again.");
        }

    }

    private static void clearScreen() {
        try {
            String os = System.getProperty("os.name").toLowerCase();
            if (os.contains("win")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                System.out.print("\033[H\033[2J");
                System.out.flush();
            }
        } catch (Exception e) {
            for (int i = 0; i < 50; i++) {
                System.out.println();
            }
        }
    }

}
