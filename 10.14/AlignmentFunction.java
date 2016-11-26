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
