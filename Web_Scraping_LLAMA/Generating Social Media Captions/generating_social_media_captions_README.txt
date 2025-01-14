This code finetunes llama 3.1 8B to generate social media captions. The generated output changes based on the social media platform.

Instructions:

Input:-------------------------
The model takes 3 parameters: description (prompt), platform and audience.

Customisation:-------------------------
Adjust qa_template if needed to refine to output more. 
Adjust the prompts, platforms and audiences lists to match the content of the posts you want to generate.

Output:-------------------------
Generated captions are displayed as text after running the cells.

Requirements:-------------------------
Run the code in Google Colab.

Libraries used:-------------------------
IPython.display
os
threading
subprocess
requests
json
lightrag.core.generator
lightrag.core.component
lightrag.core.model_client
lightrag.components.model_client
