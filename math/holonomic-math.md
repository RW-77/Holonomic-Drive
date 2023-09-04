# Holonomic Drive Calculations

For each wheel in the x-drive, two things must be determined:
1. Power supplied to each wheel
2. Direction of each wheel

The magnitude of the sum of vectors (representing wheels) in *any* direction, $\LARGE \theta$, must be constant.

We must determine a ratio between $\LARGE P_1(\theta)$ and $\LARGE P_2(\theta)$ such that:
$$
\LARGE
\begin{flalign}
\|P_1(\theta)+P_2(\theta)\|=1&&
\end{flalign}
$$
We can rotate this system so that $P_1$ and $P_2$ are horizontal and vertical vectors
Given a certain direction vector $\vec{V}$ of magnitude 1 at angle $\theta$ from the horizontal, it's horizontal and vertical components will be $P_1$ and $P_2$

$\LARGE P_1(\theta)=\vec{V}_x=\|\vec{V}\|sin{(\theta)}$ 

Since $P_1$ and $P_2$ are separated by an angle of $\frac{\pi}{2}$, $P_2$ can be written as

$\LARGE P_2(\theta)=\vec{V}_x=\|\vec{V}\|sin{(\theta-\frac{\pi}{2})}$ 

The x-drive is then simply our calculations for $P_1$ and $P_2$ rotated by $\frac{\pi}{2}$ radians counterclockwise:

$\LARGE P_1=\vec{V}_x=\|\vec{V}\|sin{(\theta+\frac{\pi}{4})}$
$\LARGE P_2=\vec{V}_y=\|\vec{V}\|sin{(\theta-\frac{\pi}{4})}$

We have successfully allocated power to each set of wheels.

$P_1$ and $P_2$ have two possible directions. We can take a dot product of the direction vector $\vec{V}$ and $P_1$ and $P_2$. The direction is simply the sign of the dot product.

We define the positive as the forward direction.

If $\vec{P}\cdot{\vec{V}}>0$, they share a direction component and $P$ is supplied power in the positive direction
If $\vec{P}\cdot{\vec{V}}<0$, they do not share a direction component and $P$ is supplied power in the negative direction
Otherwise, $P$ and $V$ are orthogonal and the direction of $P$ does not matter since it will not be supplied any power.


