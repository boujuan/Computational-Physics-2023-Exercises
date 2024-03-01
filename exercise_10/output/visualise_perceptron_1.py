import matplotlib.pyplot as plt

# Read the output file
with open('output.txt', 'r') as f:
    lines = f.readlines()

# Parse the output
iterations = []
error_rates = []
for line in lines:
    if line.startswith('#'):
        continue
    parts = line.split()
    iteration, error_rate = parts[0], parts[1]
    iterations.append(int(iteration))
    error_rates.append(float(error_rate))

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(iterations, error_rates, marker='o')
plt.title('Progress of the Perceptron')
plt.xlabel('Iteration')
plt.ylabel('Error Rate')
plt.grid(True)
plt.show()