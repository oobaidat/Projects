Objective:
Extract biography and basic information about research authors.

Instructions:
Input the author name.

IEEE Xplore:
The script includes a function that searches for the author on IEEE, the script first closes a pop up and clicks on a show more button in the biography.
Where it then extracts the author's biography and basic information.

Google Scholar:
Another function extracts the URLs of the top 10 papers when you search the author on google scholar.
Then it goes through the links and extracts the title and abstract of eahc paper.

Output:
Dictionary containing the author information.
Another dictionary containing the papers' titles and abstracts.

Requirements:
Run the code in Visual Studio.
Make sure Selenium is installed.

Libraries:
selenium