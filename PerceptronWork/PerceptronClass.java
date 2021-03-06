
public class Perceptron {
	private double[] weights;
	private static double LEARNING_RATE = 0;
	
	public Perceptron(int inputs, double rate) {
		LEARNING_RATE += rate;
		weights = new double[inputs + 1];
		for (int i = 0; i < inputs + 1; i++) {
			weights[i] = 0.0;
		}
		
	}
	
	public boolean TrainingExample(double[] data, boolean label) {
		double output = 0;
		int target = 0;
		boolean change = false;
		
		for(int i = 0; i < data.length + 1; i++) {
			if (i == 0) {
				output = output + 1 * weights[i];
			} else {
				output = output + data[i-1] * weights[i];
			}
		}
		
		if ((output > 0) != label) {
			change = true;
			if (output > 0) {
				output = 1;
				target = -1;
			} else {
				output = -1;
				target = 1;
			}
			
			double direction = target - output;
			for(int i = 0; i < data.length + 1; i++) {
				if (i == 0) {
					weights[i] = weights[i] + LEARNING_RATE * (direction) * 1;
				} else {
					weights[i] = weights[i] + LEARNING_RATE * (direction) * data[i-1];
				}
			}
		}
		return change;
	}
}
