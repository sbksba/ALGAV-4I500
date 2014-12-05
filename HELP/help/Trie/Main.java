public class Main {
    public static void main(String args[]){
        Trie object = new Trie(); //Creating a new object for Trie 
        object.insert("+0614753299","Benjy"); //Adding a phone number
        object.insert("+0146424734","Maison");

        System.out.println(object.search("+0614753299")); //Searching a number
        System.out.println(object.search("+0614753290"));

        System.out.println(object.getName("+0614753299"));
	System.out.println(object.getName("+0146424734"));	
    }
}