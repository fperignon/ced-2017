"""Un exemple de classe python, doc pour sphinx

"""


class Penalisation(object):
    """un exemple de classe ...
    """

    def __init__(self, obstacles, coeff=None):
        """

        Parameters
        ----------
        obstacles : liste
            un premier parametre
        coeff : double, optional
            un second parametre optionel

        Notes
        -----
        blabla

        """
        # le code
        self.var1 = obstacles
        self.var2 = coeff

#     def change_coeff(self, newval):
#         """Une methode de la classe

#         Parameters
#         ----------
#         newval : double, optional
#             facteur qui multiplie coeff

#         Returns
#         -------
#             la nouvelle valeur de coeff
#         """
#         self.var2 *= newval
#         return self.var2
