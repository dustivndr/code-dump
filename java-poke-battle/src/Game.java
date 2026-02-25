
import java.util.Scanner;

public class Game {

    private static final Scanner scanner = new Scanner(System.in);

    public static void gameStart() {
        System.out.println("Game started!");
        System.out.println("Starting battle...");
        sleep(200);
        clearScreen();

        for (Poke poke : Poke.getAllPokes()) {
            System.out.println(poke.pokeName + " (HP: " + poke.hp + ", Attack: " + poke.attack + ")");
        }

        System.out.println("Pick one as your Pokemon (1-" + Poke.getAllPokes().size() + "): ");
        if (!scanner.hasNextInt()) {
            System.out.println("Invalid choice.");
            scanner.nextLine();
            return;
        }
        int choice = scanner.nextInt();
        scanner.nextLine();

        if (choice < 1 || choice > Poke.getAllPokes().size()) {
            System.out.println("Invalid choice.");
            return;
        }

        Poke playerPoke = Poke.getAllPokes().get(choice - 1);
        System.out.println("You chose " + playerPoke.pokeName + "!");

        
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

    private static void sleep(int ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

}
