$$
\begin{align*}
expr & \rightarrow expr + term \; \{+\} \\
     & \mid expr - term \; \{-\} \\
     & \mid term
\end{align*}
$$
$$
\begin{align*}
term & \rightarrow term * term \; \{*\} \\
     & \mid term / term \; \{/\} \\
     & \mid factor
\end{align*}
$$

$$
\begin{align*}
factor & \rightarrow (expr)\\
     & \mid num \; \{ num.valor \} \\
     & \mid id \; \{ id.lexeme \}
\end{align*}
$$