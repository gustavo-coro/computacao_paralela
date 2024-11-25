# Load necessary libraries
library(ggplot2)

# Read the CSV file
file_path <- "time_sparse_big.csv"  # Replace with your file path
data <- read.csv(file_path, sep = ";")

# Convert columns to appropriate types (if needed)
data$Nodes <- as.numeric(data$Nodes)
data$Edges <- as.numeric(data$Edges)
data$Sequential.Time <- as.numeric(data$Sequential.Time)
data$MPI.Time <- as.numeric(data$MPI.Time)

# Summary of the dataset
summary(data)

# Scatter plots for data visualization
# Time vs. Nodes
ggplot(data, aes(x = Nodes)) +
  geom_point(aes(y = Sequential.Time, color = "Sequencial")) +
  geom_point(aes(y = MPI.Time, color = "MPI")) +
  geom_smooth(aes(y = Sequential.Time, color = "Sequencial"), method = "lm", se = FALSE) +
  geom_smooth(aes(y = MPI.Time, color = "MPI"), method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Vértices", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequencial" = "blue", "MPI" = "red"))

# Time vs. Edges
ggplot(data, aes(x = Edges)) +
  geom_point(aes(y = Sequential.Time, color = "Sequencial")) +
  geom_point(aes(y = MPI.Time, color = "MPI")) +
  geom_smooth(aes(y = Sequential.Time, color = "Sequencial"), method = "lm", se = FALSE) +
  geom_smooth(aes(y = MPI.Time, color = "MPI"), method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Arestas", x = "Número de Arestas", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequencial" = "blue", "MPI" = "red"))

# Regression Analysis
# Linear model: Tempo Sequencial ~ Nodes + Edges
lm_sequential <- lm(Sequential.Time ~ Nodes + Edges, data = data)
summary(lm_sequential)

# Linear model: MPI Time ~ Nodes + Edges
lm_mpi <- lm(MPI.Time ~ Nodes + Edges, data = data)
summary(lm_mpi)

# Comparison of growth rates
growth_rate_plot <- ggplot(data, aes(x = Nodes)) +
  geom_line(aes(y = Sequential.Time, color = "Sequencial")) +
  geom_line(aes(y = MPI.Time, color = "MPI")) +
  labs(title = "Comparação de Crescimento do Tempo de Execução", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequencial" = "blue", "MPI" = "red"))

print(growth_rate_plot)

# Save plots as images
ggsave("time_vs_nodes_big.png", width = 8, height = 5)
ggsave("time_vs_edges_big.png", width = 8, height = 5)
ggsave("growth_comparison_big.png", plot = growth_rate_plot, width = 8, height = 5)
















# Load necessary libraries
library(ggplot2)
library(reshape2)

# Read the CSV file
file_path <- "time_sparse_process.csv"  # Replace with your file path
data <- read.csv(file_path, sep = ";")

# Convert columns to appropriate types (if needed)
data$Nodes <- as.numeric(data$Nodes)
data$Edges <- as.numeric(data$Edges)
data$Sequencial <- data$Sequential.Time
data$Sequencial <- as.numeric(data$Sequential.Time)
data$MPI.2.procs <- as.numeric(data$MPI.2.procs)
data$MPI.3.procs <- as.numeric(data$MPI.3.procs)
data$MPI.4.procs <- as.numeric(data$MPI.4.procs)

# Summary of the dataset
summary(data)

# Reshape data for easier plotting with ggplot2
melted_data <- melt(data, id.vars = c("Nodes", "Edges"), 
                    variable.name = "Execution.Type", 
                    value.name = "Execution.Time")

# Rename Execution.Type for readability
melted_data$Execution.Type <- gsub("\\.", " ", melted_data$Execution.Type)

# Scatter plots for data visualization
# Time vs. Nodes
ggplot(melted_data, aes(x = Nodes, y = Execution.Time, color = Execution.Type)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Vértices", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequencial" = "blue", 
                                "MPI 2 procs" = "red", 
                                "MPI 3 procs" = "green", 
                                "MPI 4 procs" = "purple"))

# Time vs. Edges
ggplot(melted_data, aes(x = Edges, y = Execution.Time, color = Execution.Type)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Arestas", x = "Número de Arestas", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequencial" = "blue", 
                                "MPI 2 procs" = "red", 
                                "MPI 3 procs" = "green", 
                                "MPI 4 procs" = "purple"))

# Regression Analysis
# Linear model: Sequential Time ~ Nodes + Edges
lm_sequential <- lm(Sequencial ~ Nodes + Edges, data = data)
summary(lm_sequential)

# Linear models: MPI times
lm_mpi_2 <- lm(MPI.2.procs ~ Nodes + Edges, data = data)
summary(lm_mpi_2)

lm_mpi_3 <- lm(MPI.3.procs ~ Nodes + Edges, data = data)
summary(lm_mpi_3)

lm_mpi_4 <- lm(MPI.4.procs ~ Nodes + Edges, data = data)
summary(lm_mpi_4)

# Growth Comparison
growth_comparison_plot <- ggplot(melted_data, aes(x = Nodes, y = Execution.Time, color = Execution.Type)) +
  geom_line() +
  labs(title = "Comparação do Crescimento do Tempo de Execução", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequencial" = "blue", 
                                "MPI 2 procs" = "red", 
                                "MPI 3 procs" = "green", 
                                "MPI 4 procs" = "purple"))

print(growth_comparison_plot)

# Save plots as images
ggsave("time_vs_nodes_process.png", width = 8, height = 5)
ggsave("time_vs_edges_process.png", width = 8, height = 5)
ggsave("growth_comparison_process.png", plot = growth_comparison_plot, width = 8, height = 5)

