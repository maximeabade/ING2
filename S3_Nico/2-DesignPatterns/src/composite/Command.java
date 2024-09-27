package composite;

import java.util.ArrayList;
import java.util.List;

public class Command {

	private List<Article> commands = new ArrayList<Article>();
	
	public void add(Article article) {
		this.commands.add(article);
	}
	
	public void remove(Article article) {
		this.commands.remove(article);
	}
	
	public double getPrice() {
		double price = 0;
		for(Article article : commands) {
			price += article.getPrice();
		}
		
		return price;
	}
	
	
	@Override
	public String toString() {
		String res = "";
		
		for(Article article : commands) {
			res += "- " + article.toString() + " : " + article.getPrice() + "\n";
		}
		
		res += "Total : " + this.getPrice();
		
		return res;
	}
}
