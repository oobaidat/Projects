library(ggplot2)
library(gridExtra)
library(tidyr)
library(dplyr)

df <- read.csv("C:/PSUT - Data Science and AI/2024 - 2025 First/Data Visualisation/Project/Chess.csv")
head(df, 5)

# #No null values
# sum(is.na(df))

# #Drop 946 records that are duplicated
# sum(duplicated(df$game_id))
# duplicates <- df[duplicated(df) | duplicated(df, fromLast = TRUE), ]
# ordered_duplicates <- duplicates[order(duplicates$game_id), ]
df <- df[!duplicated(df$game_id), ]

# unique(df$rated)
# 
# range(df$turns)
# 
# unique(df$victory_status)
# 
# length(df$moves)
# length(unique(df$moves))
# 
# df$opening_eco
# df$opening_name
# df$opening_ply

ggplot(df, aes(x = reorder(winner, winner, FUN = length), fill = winner )) +
  geom_bar(fill=c('green', 'black', 'lightgrey')) +
  labs(x="Winner", y="Number of Wins", title="The impact of the color played on the chances of winning")+
  geom_text(stat = 'count', aes(label = ..count..), vjust = -0.5, size = 5, color = "black")+
  theme_minimal()
#There is a slight impact of the color played on the chances of winning, where white's seem to win more than black's.

ob<-head(as.data.frame(df%>%
  filter(winner=="black")%>%
  group_by(opening_name)%>%
  summarize(count=n())%>%
  arrange(desc(count)))%>%
  mutate(color='black'), 5)

ow<-head(as.data.frame(df%>%
  filter(winner=="white")%>%
  group_by(opening_name)%>%
  summarize(count=n())%>%
  arrange(desc(count)))%>%
  mutate(color='white'), 5)

fo<-rbind(ob, ow)
fo

# gn<-head(as.data.frame(df%>%
#                     group_by(opening_name)%>%
#                     summarize(count=n())%>%
#                     arrange(desc(count))), 5)

ggplot(fo, aes(x = opening_name, y = count, fill = color)) +
  geom_bar(stat = "identity", position = "dodge") +
  facet_wrap(~color, scales = "free") +
  theme_minimal() +
  theme(axis.text.x = element_text(angle = 45, hjust = 1), strip.text = element_text(size = 12, face = "bold"), legend.position = "none", panel.grid = element_blank()) +
  labs(title = "Opening Names by Count for Each Color", x = "Opening Name", y = "Count") +
  scale_fill_manual(values = c("black" = "black", "white" = "gray")) +
  scale_y_continuous(limits = c(0, 250)) +
  geom_text(aes(label = count), position = position_dodge(width = 0.9), vjust = -0.5)

# Top 5 Opening Moves For Black Pieces:
# Van't Kruijs Opening: 226
# Sicilian Defense: 194
# Sicilian Defense: Bowdler Attack: 164
# Scandinavian Defense: 123
# French Defense: Knight Variation: 121

# Top 5 Opening Moves For White Pieces:
# Scandinavian Defense: Mieses-Kotroc Variation: 164
# Sicilian Defense: 149
# Scotch Game: 145
# French Defense: Knight Variation: 135
# Philidor Defense #3: 127
# As we see here 

# Compare the Typical Openings by Color   
# Black Openings:
# The most common opening for black pieces is Van't Kruijs Opening, with 226 games.
# Aggressive defenses like Sicilian Defense and Scandinavian Defense appear prominently.
# 
# White Openings:
# The most common opening for white pieces is Scandinavian Defense: Mieses-Kotroc Variation, with 164 games.
# White also frequently employs Scotch Game and French Defense: Knight Variation.
# Both colors use variations of the Sicilian Defense.
# 
# Distinct Differences:
# Black's openings emphasize counterplay and solid defenses, such as Sicilian Defense and Scandinavian Defense.
# White tends to lean on more aggressive or classical openings like Scotch Game and variations of the French Defense.


# ggplot(df, aes(x=white_rating, y=turns))+
#   geom_point()+
#   theme_minimal()
# 
# cor.test(df$white_rating, df$turns)
# 
# 
# ggplot(df, aes(x=black_rating, y=turns))+
#   geom_point()+
#   theme_minimal()
# 
# cor.test(df$black_rating, df$turns)


ggplot(df, aes(x=(white_rating+black_rating)/2, y=turns))+
  geom_point()+
  labs(x='Average rating')+
  geom_smooth(method='lm')+
  theme_minimal()

cor.test((df$white_rating+df$black_rating)/2, df$turns)

#The relationship between number of turns a game last based on player ranking is weak but yet tells us that the higher the ratting fo rthe players is the more turns it takes and thats possible because they tend to play more strategically and avoid mistakes


data_cleaned <- df %>%
  mutate(
    opening_moves = sapply(strsplit(as.character(moves), " "), function(x) 
      paste(x[1:min(5, length(x))], collapse = " "))
  )

# Group by outcome and move patterns, then count occurrences
move_patterns_by_outcome <- data_cleaned %>%
  group_by(victory_status, opening_moves) %>%
  summarise(count = n(), .groups = "drop") %>%
  arrange(victory_status, desc(count))

# Display top patterns for wins and losses
win_patterns <- move_patterns_by_outcome %>%
  filter(victory_status == "mate") %>%
  slice(1:5)

loss_patterns <- move_patterns_by_outcome %>%
  filter(victory_status == "resign") %>%
  slice(1:5)

print("Top move patterns leading to wins:")
print(as.data.frame(win_patterns))

print("Top move patterns leading to losses:")
print(loss_patterns)

ranking_patterns <- data_cleaned %>%
  mutate(avg_rating = (white_rating + black_rating) / 2) %>%
  group_by(victory_status, opening_moves) %>%
  summarise(
    avg_rating = mean(avg_rating, na.rm = TRUE),
    count = n(),
    .groups = "drop"
  ) %>%
  arrange(victory_status, desc(avg_rating))

print("Move patterns by player ranking:")
print(ranking_patterns %>% slice(1:5))

data_cleaned <- data_cleaned %>%
  mutate(game_length_category = case_when(
    turns < 20 ~ "Short",
    turns >= 20 & turns < 50 ~ "Medium",
    turns >= 50 ~ "Long"
  ))

# Group by duration and outcome
duration_patterns <- data_cleaned %>%
  group_by(game_length_category, victory_status, opening_moves) %>%
  summarise(count = n(), .groups = "drop") %>%
  arrange(game_length_category, victory_status, desc(count))

print("Move patterns by game duration:")
print(duration_patterns %>% slice(1:5))

# Define the range for the unified y-axis
y_axis_limit <- c(0, max(c(win_patterns$count, loss_patterns$count)))

# Define the two plots with specific colors and unified y-axis
win_plot <- ggplot(win_patterns, aes(x = reorder(opening_moves, count), y = count, fill = victory_status)) +
  geom_bar(stat = "identity") +
  scale_fill_manual(values = c("mate" = "blue")) + # Specific color for win plot
  labs(title = "Top Patterns Leading to a Win", x = "Opening Moves", y = "Frequency") +
  theme_minimal() +
  theme(panel.grid = element_blank()) +
  ylim(y_axis_limit)

loss_plot <- ggplot(loss_patterns, aes(x = reorder(opening_moves, count), y = count, fill = victory_status)) +
  geom_bar(stat = "identity") +
  scale_fill_manual(values = c("resign" = "red")) + # Specific color for loss plot
  labs(title = "Top Patterns Leading to a Loss", x = "Opening Moves", y = "Frequency") +
  theme_minimal() +
  theme(panel.grid = element_blank()) +
  ylim(y_axis_limit)

# Combine the plots side by side
grid.arrange(win_plot, loss_plot, ncol = 2)

# 
# Winning Patterns (Mate): Common winning sequences include openings such as e4 e5 Nf3 Nc6 Bc4 and e4 e5 Nf3 Nc6 Bb5, often leading to victory through strategic follow-ups.  
# Losing Patterns (Resignation): The same openings, e4 e5 Nf3 Nc6 Bc4 and e4 e5 Nf3 Nc6 Bb5, frequently appear in losses, emphasizing that outcomes depend more on mid-game decisions than the initial moves.  
# Player Rankings: Players with higher ratings (above 2300) display a wider range of opening strategies, reflecting greater tactical flexibility and depth.  
# Game Length: Short matches, typically under 20 turns, are often marked by openings like e4 e5 Nf3 Nc6 Bc4, with early resignations signaling decisive mistakes or rapid checkmates.    

