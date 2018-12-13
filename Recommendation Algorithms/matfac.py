import numpy as np


def train(users, objects, training, lr=1e-3, epochs=1000):
    for _ in range(epochs):  # iterations
        for u, v, r in training:  # for each rating r & the associated user u & object v
            # dloss / duser = (what we predict - what we want) * object vector
            u_grads = ((users[u, :] @ objects[:, v] - r) * objects[:, v])

            # dloww / dobject = (what we predict - what we want) * user vector
            v_grads = ((users[u, :] @ objects[:, v] - r) * users[u, :])

            # do updates
            users[u, :] -= lr * u_grads.T  # transpose because object vectors are columns
            objects[:, v] -= lr * v_grads.T  # transpose becuase user vectors are rows

    return users, objects

# user & object indices. shape: [30]
# ratings matrix shape: [10, 15] (10 users & 15 objects)
uu = np.random.randint(0, 10, 30)
vv = np.random.randint(0, 15, 30)

# ratings. shape: [30]
rr = np.random.normal(size=30)

# (u, v, r) tuples.
# u: user index
# v: objecti index
# r: user u rated v the score r
# this data has been initialized randomly to have an easy example
training = list(zip(uu, vv, rr))

# random matrix for all users (gaussian = normal distribution)
# shape: [10, 5] where 10 is the number of users
users = np.random.normal(size=(10, 5))

# random matrix for objects
# shape: [5, 15] where 15 is the number of objects
objects = np.random.normal(size=(5, 15))

# train to get t_uu: user matrix, t_vv: object matrix
t_uu, t_vv = train(users, objects, training)

# target is ratings matrix. we make it an actual matrix for
# visualization purposes
target = np.zeros((10, 10))
target[uu, vv] = rr

print(target)
print(t_uu @ t_vv)

# calculate loss. should be relativel small
loss = ((t_uu @ t_vv)[uu, vv] - rr)**2
print(loss.mean())
