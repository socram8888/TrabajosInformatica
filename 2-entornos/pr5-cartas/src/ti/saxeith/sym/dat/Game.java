/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.dat;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.util.Stack;

/**
 *
 * @author Marcos
 */
public class Game {
    private Stack<Card> stack;
    private final List<Player> players;
    private int firstPlayer;

    private int playingId;
    private int playCount = 1;
    private int finishedCount;

    public Game(int playerCount) {
        stack = StackFactory.create();

        players = new ArrayList<Player>();
        for (int i = 0; i < playerCount; i++) {
            String name;

            if (i == 0) {
                name = "Banca";
            } else {
                name = "Jugador " + i;
            }

            Player player = new Player(this, i, name, i == 0);
            players.add(player);
        }

        firstPlayer = playingId = (new Random()).nextInt(playerCount);
        doAI();
    }

    public Stack<Card> getStack() {
        return stack;
    }

    public List<Player> getPlayers() {
        return players;
    }

    public Player getPlayingPlayer() {
        if (isFinished()) {
            return null;
        }
        return players.get(playingId);
    }

    public void requestCard() {
        if (isFinished()) {
            return;
        }

        Player current = players.get(playingId);
        current.requestCard();
        if (current.hasLost()) {
            passPlayer();
        }
    }

    public void passPlayer() {
        if (isFinished()) {
            return;
        }

        playingId = (playingId + 1) % players.size();

        if (playingId == firstPlayer) {
            playingId = -1;

            Set<Player> winners = getWinners();
            for (Player player : players) {
                if (winners != null && winners.contains(player)) {
                    player.setWonCount(player.getWonCount() + 1);
                }
            }
            
            finishedCount++;
            
            return;
        }
        
        doAI();
    }

    public int getBestSum() {
        int bestSum = 0;

        for (Player player : players) {
            int sum = player.getSevenHalfSum();
            if (sum <= 75 && sum > bestSum) {
                bestSum = sum;
            }
        }
        
        return bestSum;
    }

    public Set<Player> getWinners() {
        if (!isFinished()) {
            return null;
        }

        int bestSum = getBestSum();
        
        Set<Player> winners = new HashSet<Player>();
        for (Player player : players) {
            if (player.getSevenHalfSum() == bestSum) {
                winners.add(player);
            }
        }

        return winners;
    }
    
    public void playAgain() {
        Set<Player> winners = getWinners();
        stack = StackFactory.create();

        for (Player player : players) {
            player.playAgain();
        }

        playCount++;
        int playerCount = players.size();
        firstPlayer = playingId = (new Random()).nextInt(playerCount);
        
        doAI();
    }

    public int getPlayCount() {
        return playCount;
    }

    public int getFinishedCount() {
        return finishedCount;
    }
    
    private void doAI() {
        Player player = getPlayingPlayer();
        if (player.isAI()) {
            while (!player.hasLost() && (player.getSevenHalfSum() < 40 || getBestSum() > player.getSevenHalfSum())) {
                player.requestCard();
            }
            if (getPlayingPlayer() == player) {
                passPlayer();
            }
        }
    }
    
    public boolean isFinished() {
        return playingId < 0;
    }
}
