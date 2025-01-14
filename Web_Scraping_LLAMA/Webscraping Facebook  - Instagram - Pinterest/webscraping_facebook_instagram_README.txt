This code scrapes posts from Facebook and Instagram using the same approach for both platforms.

Instructions:

Login Credentials:-------------------------
Enter your username and password where indicated in the code.

Post URL Extraction:-------------------------
The script includes a function that extracts the URLs of posts from each account. You can control the pages that you scrape by altering the pages lists. You can also adjust the number of posts you scrape by changing the scroll range in the code.
'for scroll in range(0, 1):'

Image and Caption Extraction:-------------------------
Another function takes each post's URL and extracts the image and caption. Threading is used to make the process faster.

Data Storage:-------------------------
The data is saved into two dataframes: facebook_captions_df and instagram_captions_df.

Requirements:-------------------------
Run the code in Visual Studio.
Make sure Selenium is installed.

Libraries used:-------------------------
selenium
time
multiprocessing
pandas
threading
concurrent.futures

