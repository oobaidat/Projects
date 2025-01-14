library(dplyr)
library(ggplot2)
library(tsibble)
library(fpp3)
library(slider)

df <- read.csv("C:/PSUT - Data Science and AI/2024 - 2025 First/Data Visualisation/Assignment 2/state_long_dataset.csv")
head(df)


# -------------------Q1-------------------
covid <- df |> 
        filter(State == "Florida") |>
        mutate(DATE = as.Date(DATE)) |>
        as_tsibble(index = DATE)
str(covid)
summary(covid)
# only after 40 days we get infected people
covid[38:43,]


# -------------------Q2-------------------
covidDaily <- covid |>
            mutate(NewInfected = Infected - lag(Infected)) |>
            mutate(NewDeaths = Death - lag(Death))

head(covidDaily)
# fill the first row with 0 as new infected/deaths
covidDaily[is.na(covidDaily)] <- 0

autoplot(covidDaily, NewInfected) +
  labs(title = "New Daily COVID Infections in Florida",
  y = "Count")

autoplot(covidDaily, NewDeaths) +
  labs(title = "New Daily COVID Deaths in Florida",
  y = "Count")

# We can see two peaks in COVID infections in Florida, once around July 2020 and the next in January 2021
# This follows reports of how typical viruses spread with seasonal peaks potentially in our data around every 6 months

# We can see that deaths caused by COVID in Florida follow a similar trend to the infections, but slightly lagged
# Where the first peak was between July and August of 2020 and we can see a clear trend of increasing deaths around January which is the peak of infections 


# -------------------Q3-------------------
dcmp <- covidDaily |>
  model(
    STL(NewInfected ~ trend(window = 7) + season(window = "periodic"), robust = TRUE)
    ) 

components <- dcmp |>
              components()

components |>
  autoplot() +
  theme_bw()


# Trend: is very similar to the original data
# Seasonality: since our data is daily, a weekly seasonality was applied,
# and we can see that there is no seasonality as there is no clear pattern
# Noise: We can see clear outliers that don't fit the trend in the original data in the last couple of months,
# the noise captures those data


# -------------------Q4-------------------
covidDaily |>
  gg_subseries(y = NewInfected, period = "week") +
  theme_bw()
# In the first weekly graph we can see that the average for each day of the week peeks around Thursday - Saturday,
# but it is a very minimal effect

covidDaily |>
  gg_season(NewInfected, period = "week") +
  theme_bw()
# And in the second weekly graph, it's kind of hard to see, especially the last weeks where it becomes very hard to read

covidDaily |>
  gg_season(NewInfected, period = "month") +
  theme_bw()
# No month seasonality, everything looks mixed up


# -------------------Q5-------------------
covidSmooth <- covidDaily |>
  mutate(
    `7-MA` = slider::slide_dbl(NewInfected, mean,
                               .before = 3, .after = 3, .complete = TRUE)
  )

covidSmooth |>
  autoplot(NewInfected) +
  geom_line(aes(y = `7-MA`), colour = "#D55E00", linewidth = 1.2) +
  labs(title = "Original vs Adjusted Daily New Cases") +
  theme_bw()


# -------------------Q6-------------------
covidMid <- df |> 
  filter(Region == "Midwest") |>
  mutate(DATE = as.Date(DATE)) |>
  as_tsibble(key = State, index = DATE) |>
  group_by(State) |>
  mutate(NewDeaths = Death - lag(Death)) |>
  ungroup()
covidMid[is.na(covidMid)] <- 0

covidMid |>
  autoplot(NewDeaths) +
  facet_wrap(~ State) +
  theme_bw()
# Illinois and Michigan have two very large peaks in accordance to the infection peaks we saw similar to Florida
# Other states handled the deaths better, having lower peaks, with some only having one peak with the second outbreak only
# Kansas, Nebraska, North Dakota, and South Dakota handled the outbreak very well, almost not exceeding 50 deaths per day ever


# -------------------Q7-------------------
covidWeekly <- covidDaily |>
  index_by(Week = yearweek(DATE)) |>
  summarise(NewDeaths = sum(NewDeaths))

covidWeekly |>
  autoplot(NewDeaths) +
  labs(title = "Weekly New Deaths in Florida") +
  theme_bw()
# Similar to moving average we more easily see the trend in the deaths now, making it easier to tell when the peaks happen
# But it's different as we are taking weekly averages, making our data 7 times smaller
# This would also remove any weekly seasonality that exists, but as we saw there is no indication of such


# -------------------Q8-------------------
covidDaily |>
  gg_lag(NewInfected, geom = "point", size = 2) +
  labs(x = "lag(NewInfected, k)") +
  theme_bw()

covidDaily |>
  ACF(NewInfected) |>
  autoplot() + labs(title="New Daily Infections in Florida") +
  theme_bw()
# Both show that there is a high positive autocorrelation in the data,
# where in the ACF we can see that it never drops below the threshold
# Since there are no clear trends every kth lag, this indicates that my previous conclusion about no seasonality is likely correct


# -------------------Q9-------------------
ccf(covidDaily$NewInfected, covidDaily$NewDeaths, plot = TRUE)

covidDaily |>
  ggplot(aes(x = lag(NewInfected, n = 19), y = NewDeaths)) +
  geom_point() +
  geom_smooth(method = "lm", se = FALSE, color = "blue") +
  theme_bw()

cor(lag(covidDaily$NewInfected, n = 19), covidDaily$NewDeaths, use = "complete.obs")
# By applying a cross correlation to see the correlation between the variables at different lags
# we can see that at around lag -19 is when the correlation was highest, when calculated being around 0.73
# This indicates that there is a high correlation between someone getting infected with COVID and someone dying from COVID after around 19 days 


