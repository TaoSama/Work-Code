## Dynamic Programming for DNA Aligning

* Explanation

  $result[i][j]:=the\ maximum\ score\ when\ try\ to\ match\ the\ s1_i\ with\ s2_j,\ at\ the\ same\ time\ record\ the\ direction$

  $the\ transition\ is\ somehow\ like\ the\ classic\ problem\ "LCS"$

  $after\ some\ observation,\ we\ can\ find\ out\ that\ as\ for\ s1_i\ and\ s2_j,\ it\ is\ equivalent\ when\ delete\ one\ of\ them\ or\ insert\ a\ space$

  $so,\ we\ just\ concern\ about\ inserting\ a\ space$

  $result[i + 1][j + 1] = max(result[i + 1][j + 1], result[i][j] + 2),\ iff\ s1_i==s2_j$

  $result[i + 1][j] = max(result[i + 1][j], result[i][j] - 1),\ insert\ a\ space\ before\ s_{i+1}\ to\ match\ s2_j$

  $result[i][j + 1] = max(result[i][j + 1], result[i][j] - 1),\ insert\ a\ space\ before\ s_{j+1}\ to\ match\ s1_i$

  $obviously,\ the\ maximum\ score\ at\ last\ is\ result[s1.length][s2.length]$

  $we\ can\ easily\ recover\ the\ two\ strings\ through\ the\ directions\ we\ recorded$

* My Code

  ```cpp
  public class AlignmentFunction {

      static Result[][] align(String s1, String s2,
  			    StringBuilder s1_aligned, StringBuilder s2_aligned) {
  	// put your solution here
  		Result[][] result = new Result[s1.length() + 1][s2.length() + 1];
  		for(int i = 0; i <= s1.length(); ++i)
  			for(int j = 0; j <= s2.length(); ++j)
  				result[i][j] = new Result(-1000, Mutation.M);
  		
      	result[0][0] = new Result(0, Mutation.M);
      	
      	for(int i = 0; i <= s1.length(); ++i){
      		for(int j = 0; j <= s2.length(); ++j){
      			if(i < s1.length() && j < s2.length()){
      				if(s1.charAt(i) == s2.charAt(j)){
      					int score = result[i][j].score + Constants.MATCH;
      					if(result[i + 1][j + 1].score < score){
      						result[i + 1][j + 1] = new Result(score, Mutation.M);
      					}
      				}
      			}
  				if(i + 1 <= s1.length()){
  					int score = result[i][j].score + Constants.SPACE_PENALTY;
  					if(result[i + 1][j].score < score){
  						result[i + 1][j] = new Result(score, Mutation.I);
  					}
  				}
  				if(j + 1 <= s2.length()){
  					int score = result[i][j].score + Constants.SPACE_PENALTY;
  					if(result[i][j + 1].score < score){
  						result[i][j + 1] = new Result(score, Mutation.I);
  					}
  				}
      		}
      	}
      	
  //    	for(int i = 0; i <= s1.length(); ++i){
  //    		for(int j = 0; j <= s2.length(); ++j){
  //    			System.out.printf("%d ", result[i][j].score);
  //    		}
  //    		System.out.println("");
  //    	}
      	
      	int i = s1.length(), j = s2.length();
      	while(i > 0 || j > 0){
      		if(i > 0 && j > 0 && result[i][j].dir == Mutation.M){
      			--i;
      			--j;
      			s1_aligned.append(s1.charAt(i));
      			s2_aligned.append(s2.charAt(j));
      		}
      		else if(j > 0 && result[i][j].dir == Mutation.I){
      			--j;
      			s1_aligned.append(Constants.SPACE_CHAR);
      			s2_aligned.append(s2.charAt(j));
      		}
      		else if(i > 0 && result[i][j].dir == Mutation.I){
      			--i;
      			s1_aligned.append(s1.charAt(i));
      			s2_aligned.append(Constants.SPACE_CHAR);
      		}
      		else{
      			System.out.println("fuck +" + i + " " + j);
      			break;
      		}
      	}
  		return result;
      }
  }
  ```

  ​

