
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Poke {

    String pokeName, pokeType;
    int hp;
    int attack;

    public Poke(String pokeName, String pokeType, int hp, int attack) {
        this.pokeName = pokeName;
        this.pokeType = pokeType;
        this.hp = hp;
        this.attack = attack;
    }

    private static final List<Poke> allPokes = new ArrayList<>();

    static final Poke charizard = addPoke("Charizard", "Fire", 360, 84);
    static final Poke blastoise = addPoke("Blastoise", "Water", 362, 83);
    static final Poke venusaur = addPoke("Venusaur", "Grass", 362, 82);
    static final Poke pikachu = addPoke("Pikachu", "Electric", 274, 55);

    private static Poke addPoke(String pokeName, String pokeType, int hp, int attack) {
        Poke poke = new Poke(pokeName, pokeType, hp, attack);
        allPokes.add(poke);
        return poke;
    }

    static List<Poke> getAllPokes() {
        return Collections.unmodifiableList(allPokes);
    }

}
