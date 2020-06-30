    # --------------------------------------------------------------------------
    # Handwritten methods for Rot3
    # These will get included into the autogenerated class header.
    # --------------------------------------------------------------------------

    def __init__(self, q=None):
        if q is None:
            self.data = ops.GroupOps.identity()
        else:
            assert len(q) == self.storage_dim()
            self.data = list(q)

    # TODO rotation helpers