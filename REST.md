# API specification

## Methods

### **GET** _/topics_

`returns` all the topics in a json string. Example:
```js
[
    "physics", "math", "computers"
]
```

### **GET** _/users/:id/likes_

`:id` user ID provided by the GUI

`returns` a json object whose keys are all the topics, and values are `1` for a like and `0` for the absence of a like. Example:
```js
{
    "physics": 0,
    "math": 1,
    "computers": 1
}
```

`details` given an _existing_ user ID, request the topic likes of this user ; the user MUST exist before this method is called.

### **PUT** _/users/:id/likes_

`:id` user ID provided by the GUI

`body` a json object whose keys are all the topics, and values are `1` for a like and `0` for the absence of a like. Example:
```js
{
    "physics": 0,
    "math": 1,
    "computers": 1
}
```

`returns` a json object whose unique key is `"success"` and whose value is `1` on success and `0` on failure.
```js
{
    "success": 1
}
```

`details` if the user given _doesn't exist_, create the user ; store the user's likes given in the request body.

### **GET** _/users/:id/recommendation_

`:id` user ID provided by the GUI

`returns` a json object whose unique key is `"article"` and whose value is the ID of the article the recommendation service produced. Example:
```js
{
    "article": "1812.01234_v2"
}
```

`details` this method calls the recommendation service to produce an article to recommend to the user given through `:id` ; the user MUST exists before this method is called.

### **GET** _/users/:id/articles_

`:id` user ID provided by the GUI

`returns` all the liked articles in a json string. Example:
```js
[
    "1812.01234_v2", "1609.43210"
]
```

`details` the user MUST exist before this method is called.

### **POST** _/users/:id/articles_

`:id` user ID provided by the GUI

_POST fields_

`article` article ID. Example: `article=1812.01234_v2`

`returns` a json object whose unique key is `"success"` and whose value is `1` on success and `0` on failure.
```js
{
    "success": 1
}
```

`details` this methods creates an edge between the user and the paper which will be used to refine the recommendation algorithm ; the user MUST be called before this method is called.
