package com.parc.ccn.network.daemons.repo;

import java.util.ArrayList;

import com.parc.ccn.data.ContentName;
import com.parc.ccn.data.ContentObject;
import com.parc.ccn.data.query.Interest;
import com.parc.ccn.library.CCNLibrary;

/**
 * Designed to contain all methods that talk to the repository
 * directly so that we can easily replace the repository with a
 * different implementation.  
 * 
 * @author rasmusse
 *
 */

public interface Repository {

	public static final String REPO_POLICY = "policy.xml";
	public static final String REPO_NAMESPACE = "/ccn/repository";
	public static final String REPO_DATA = "data";
	
	/**
	 * Initialize the repository
	 * @param args - user arguments to the repository
	 * @return
	 */
	public String[] initialize(String[] args, CCNLibrary library) throws RepositoryException;
	
	/**
	 * Save the specified content in the repository
	 * @param content
	 */
	public void saveContent(ContentObject content) throws RepositoryException;
	
	/**
	 * Return the matching content if it exists
	 * @param name
	 * @return
	 */
	public ContentObject getContent(Interest interest) throws RepositoryException;
	
	/**
	 * Get namespace interest
	 * @return
	 */
	public ArrayList<ContentName> getNamespace();
	
	/**
	 * Set the policy with XML based policy
	 * @param policy
	 */
	public void setPolicy(Policy policy);
	
	/**
	 * Get information about repository to return to write
	 * requestor, possibly with confirmation filename for sync
	 * 
	 * @return
	 */
	public byte [] getRepoInfo(ArrayList<ContentName> names);
	
	/**
	 * Check whether data is a policy update. Update the
	 * policy if so
	 * @param co
	 * @return true if policy update data
	 * @throws RepositoryException 
	 */
	public boolean checkPolicyUpdate(ContentObject co) throws RepositoryException;
		
	/**
	 * Get names to respond to name enumeration requests
	 * @param Interest
	 * @return ArrayList<ContentName>
	 */
    public ArrayList<ContentName> getNamesWithPrefix(Interest i);
    
    /**
     * 
     */
    public void shutDown();
    
    /**
     * Execute diagnostic operation.  The diagnostic operations are 
     * particular to the implementation and are intended for testing
     * and debugging only.
     * @param name the name of the implementation-specific diagnostic operation to perform
     * @return true if diagnostic operation is supported and was performed, false otherwise
     */
    public boolean diagnostic(String name);
}
