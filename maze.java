package tp6_inf2010;

import java.util.*;

// Classe a remplir pour realiser le TP en utilisant la classe DisjointSet fournie

public class Maze{

	public Maze(int w, int h, int seed){
		width = w;
		height = h;

		LASTROOM = width*height-1;

		// Initialisation du labyrinthe avec tous les murs
		maze = new Vector<Wall>();

	        // A completer
                for(int j=0;j<height;j++)
                    for(int i=0;i<width;i++)
                    {
                        if(j>0)
                           maze.add(new Wall(i*height,i+((j-1)*height)));
                        if(i>0)
                           maze.add(new Wall(i*height,j+((i-1)*height))); 
                    }

		// Creation du graphe de la topologie du labyrinthe

		  // A completer		
                graph=new Vector<Room>();
                for(int i=0;i<height*width;i++)
                {
                    graph.add(new Room(i));
                }
                
		// On trie les murs de maniere aleatoire
		generator = new Random(seed);
                Wall tmp = null;
                int position;
		for(int i = 0; i < maze.size(); ++i)
                {
			// A completer
                    position=Math.abs(generator.nextInt()% maze.size());
                    tmp=maze.get(position);
                    maze.set(position,maze.get(i));
                    maze.set(i, tmp);                   
		}

		// Initialisation des structures annexes
		ds = new DisjointSet(width*height);
		path = new Vector<Integer>();
	}

	public void generate(){
		// A completer
            int firstRoom;
            int secondRoom;
            for(int i=0;i<maze.size();++i)
            {
                firstRoom=maze.get(i).room1;
                secondRoom=maze.get(i).room2;
                if(ds.find(firstRoom)!=ds.find(secondRoom))
                {
                    maze.remove(i--);
                    ds.union(ds.find(firstRoom),ds.find(secondRoom));
                    graph.get(firstRoom).paths.add(graph.get(secondRoom).id);
                    graph.get(secondRoom).paths.add(graph.get(firstRoom).id);
                }
            }
	}

	public void solve(){
		// A completer
	}

	public class Wall{
		
		public Wall(int r1, int r2){
			room1 = r1;
			room2 = r2;
		}

		public int room1;
		public int room2;
	}

	public class Room{
		
		public Room(int i){
			id = i;
			distance = -1;
			paths = new Vector<Integer>();
		}

		public int id;
		Vector<Integer> paths;
		int distance;		

	}

	public Vector<Wall> maze;
	public Vector<Room> graph;
	public Vector<Integer> path;

	public int LASTROOM;
	public int height;
	public int width;
	public Random generator;
	public DisjointSet ds;
}

