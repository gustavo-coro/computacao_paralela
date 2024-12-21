# Load necessary libraries
library(ggplot2)

# Read the CSV file
file_path <- "time_dense_big.csv"  # Replace with your file path
data <- read.csv(file_path, sep = ";")

# Convert columns to appropriate types (if needed)
data$Nodes <- as.numeric(data$Nodes)
data$Edges <- as.numeric(data$Edges)
data$Sequential.Time <- as.numeric(data$Sequential.Time)
data$OMP.Time <- as.numeric(data$OMP.Time)

# Summary of the dataset
summary(data)

# Scatter plots for data visualization
# Time vs. Nodes
ggplot(data, aes(x = Nodes)) +
  geom_point(aes(y = Sequential.Time, color = "Sequential")) +
  geom_point(aes(y = OMP.Time, color = "OMP")) +
  geom_smooth(aes(y = Sequential.Time, color = "Sequential"), method = "lm", se = FALSE) +
  geom_smooth(aes(y = OMP.Time, color = "OMP"), method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Vértices", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequential" = "blue", "OMP" = "red"))

# Time vs. Edges
ggplot(data, aes(x = Edges)) +
  geom_point(aes(y = Sequential.Time, color = "Sequential")) +
  geom_point(aes(y = OMP.Time, color = "OMP")) +
  geom_smooth(aes(y = Sequential.Time, color = "Sequential"), method = "lm", se = FALSE) +
  geom_smooth(aes(y = OMP.Time, color = "OMP"), method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Arestas", x = "Número de Arestas", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequential" = "blue", "OMP" = "red"))

# Regression Analysis
# Linear model: Tempo Sequential ~ Nodes + Edges
lm_sequential <- lm(Sequential.Time ~ Nodes + Edges, data = data)
summary(lm_sequential)

# Linear model: OMP Time ~ Nodes + Edges
lm_omp <- lm(OMP.Time ~ Nodes + Edges, data = data)
summary(lm_omp)

# Comparison of growth rates
growth_rate_plot <- ggplot(data, aes(x = Nodes)) +
  geom_line(aes(y = Sequential.Time, color = "Sequential")) +
  geom_line(aes(y = OMP.Time, color = "OMP")) +
  labs(title = "Comparação de Crescimento do Tempo de Execução", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequential" = "blue", "OMP" = "red"))

print(growth_rate_plot)

# Save plots as images
ggsave("time_vs_nodes_big.png", width = 8, height = 5)
ggsave("time_vs_edges_big.png", width = 8, height = 5)
ggsave("growth_comparison_big.png", plot = growth_rate_plot, width = 8, height = 5)
















# Load necessary libraries
library(ggplot2)
library(reshape2)

# Read the CSV file
file_path <- "testes/dense/time_dense_range.csv"  # Replace with your file path
data <- read.csv(file_path, sep = ";")

# Convert columns to appropriate types (if needed)
data$Nodes <- as.numeric(data$Nodes)
data$Edges <- as.numeric(data$Edges)
data$Sequential <- data$Sequential.Time
data$Sequential <- as.numeric(data$Sequential.Time)
data$OMP.2.THREADS <- as.numeric(data$OMP.2.THREADS)
data$OMP.3.THREADS <- as.numeric(data$OMP.3.THREADS)
data$OMP.4.THREADS <- as.numeric(data$OMP.4.THREADS)

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
  scale_color_manual(values = c("Sequential" = "gray", 
                                "OMP 2 THREADS" = "red", 
                                "OMP 3 THREADS" = "green", 
                                "OMP 4 THREADS" = "purple"))

ggsave("time_vs_nodes_process_dense_range.png", width = 8, height = 5)

# Time vs. Edges
ggplot(melted_data, aes(x = Edges, y = Execution.Time, color = Execution.Type)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE) +
  labs(title = "Tempo de Execução vs Arestas", x = "Número de Arestas", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequential" = "gray", 
                                "OMP 2 THREADS" = "red", 
                                "OMP 3 THREADS" = "green", 
                                "OMP 4 THREADS" = "purple"))

ggsave("time_vs_edges_process_dense_range.png", width = 8, height = 5)

# Regression Analysis
# Linear model: Sequential Time ~ Nodes + Edges
lm_sequential <- lm(Sequential ~ Nodes + Edges, data = data)
summary(lm_sequential)

# Linear models: OMP times
lm_omp_2 <- lm(OMP.2.THREADS ~ Nodes + Edges, data = data)
summary(lm_omp_2)

lm_omp_3 <- lm(OMP.3.THREADS ~ Nodes + Edges, data = data)
summary(lm_omp_3)

lm_omp_4 <- lm(OMP.4.THREADS ~ Nodes + Edges, data = data)
summary(lm_omp_4)

# Growth Comparison
growth_comparison_plot <- ggplot(melted_data, aes(x = Nodes, y = Execution.Time, color = Execution.Type)) +
  geom_line() +
  labs(title = "Comparação do Crescimento do Tempo de Execução", x = "Número de Vértices", y = "Tempo de Execução") +
  theme_minimal() +
  scale_color_manual(values = c("Sequential" = "gray", 
                                "OMP 2 THREADS" = "red", 
                                "OMP 3 THREADS" = "green", 
                                "OMP 4 THREADS" = "purple"))

ggsave("growth_comparison_process_dense_range.png", plot = growth_comparison_plot, width = 8, height = 5)

print(growth_comparison_plot)
